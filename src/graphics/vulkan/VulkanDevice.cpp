//
// Created by Nemesis Verstraete on 16/07/2026.
//

#include "VulkanDevice.h"

#include "../../utils/Logger.h"
#include "VulkanBuffer.h"
#include "VulkanTexture.h"

namespace obsidium::vulkan {

VulkanDevice::VulkanDevice(VulkanContext& context, VulkanSurface& surface) : context(context) {
    createPhysicalDevice();
    createDevice(surface);
}

uint32_t VulkanDevice::findMemoryType(const uint32_t typeFilter, const vk::MemoryPropertyFlags properties) const {
    const vk::PhysicalDeviceMemoryProperties memoryProperties = physicalDevice.getMemoryProperties();

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    LOG_FATAL("failed to find suitable memory type");
    return ~0;
}

std::unique_ptr<VulkanBuffer> VulkanDevice::createVulkanBuffer(const size_t size, const BufferType bufferType) const {
    vk::BufferUsageFlags usage;

    switch (bufferType) {
        case BufferType::IndexBuffer:
            usage = vk::BufferUsageFlagBits::eIndexBuffer;
            break;
        case BufferType::VertexBuffer:
            usage = vk::BufferUsageFlagBits::eVertexBuffer;
            break;
        case BufferType::UniformBuffer:
            usage = vk::BufferUsageFlagBits::eUniformBuffer;
            break;
    }
    const vk::BufferCreateInfo bufferInfo{
        .size = size,
        .usage = usage,
        .sharingMode = vk::SharingMode::eExclusive
    };
    auto buffer = vk::raii::Buffer(device, bufferInfo);

    const vk::MemoryRequirements memoryRequirements = buffer.getMemoryRequirements();
    const vk::MemoryAllocateInfo allocInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, bufferAllocationMemoryProperties)
    };
    auto bufferMemory = vk::raii::DeviceMemory(device, allocInfo);
    buffer.bindMemory(bufferMemory, 0);

    return std::make_unique<VulkanBuffer>(std::move(buffer), std::move(bufferMemory),
        bufferMemory.mapMemory(0, size), size);
}

// --- physical device ---
bool VulkanDevice::isDeviceSuitable(vk::raii::PhysicalDevice const &physicalDevice,
    std::vector<char const *> requirdDeviceExtensions) {
        bool supportsVK13 = physicalDevice.getProperties().apiVersion >= vk::ApiVersion13;

        auto queueFamilies = physicalDevice.getQueueFamilyProperties();
        bool supportsGraphics = std::ranges::any_of(queueFamilies, [](auto const & qfp){ return !!(qfp.queueFlags & vk::QueueFlagBits::eGraphics); });

        auto availableExtensions = physicalDevice.enumerateDeviceExtensionProperties();
        bool supportsAllReqExt = std::ranges::all_of(requirdDeviceExtensions, [&availableExtensions](auto const & reqDevExt) {
            return std::ranges::any_of(availableExtensios, [reqDevExt](auto const & availableDevExt) {
                return strcmp(reqDevExt, availableDevExt.extensionName) == 0;
            });
        });

        auto features = physicalDevice.getFeatures2<vk::PhysicalDeviceFeatures2,
            vk::PhysicalDeviceVulkan11Features, vk::PhysicalDeviceVulkan13Features,
            vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT, vk::PhysicalDeviceDescriptorIndexingFeatures>();

        auto supportsReqFeatures = features.get<vk::PhysicalDeviceFeatures2>().features.samplerAnisotropy &&
            features.get<vk::PhysicalDeviceVulkan11Features>().shaderDrawParameters &&
                features.get<vk::PhysicalDeviceVulkan13Features>().dynamicRendering &&
                    features.get<vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>().extendedDynamicState &&
                        features.get<vk::PhysicalDeviceDescriptorIndexingFeatures>();

        return supportsVK13 && supportsReqFeatures && supportsAllReqExt && supportsGraphics;
}

std::unique_ptr<rhi::Texture> VulkanDevice::createTexture(const int width, const int height,
    const TextureUsage textureUsage, const TextureFormat format) const {
    const vk::ImageCreateInfo imageInfo{
        .imageType = vk::ImageType::e2D,
        .format = toVulkanFormat(format),
        .extent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height), 1},
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = vk::SampleCountFlagBits::e1,
        .tiling = vk::ImageTiling::eOptimal,
        .usage = vk::ImageUsageFlagBits::eSampled,
        .sharingMode = vk::SharingMode::eExclusive
    };

    auto image = vk::raii::Image(device, imageInfo);

    constexpr vk::MemoryPropertyFlags imageProperties = vk::MemoryPropertyFlagBits::eHostCoherent |
        vk::MemoryPropertyFlagBits::eHostVisible;

    const vk::MemoryRequirements memoryRequirements = image.getMemoryRequirements();
    const vk::MemoryAllocateInfo allocInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, imageProperties)
    };
    auto memory = vk::raii::DeviceMemory(device, allocInfo);
    image.bindMemory(memory, 0);

    void* mapped = memory.mapMemory(0, memoryRequirements.size);
    memcpy(mapped, data, memoryRequirements.size);

    const vk::ImageViewCreateInfo viewInfo{
        .image = image,
        .viewType = vk::ImageViewType::e2D,
        .format = toVulkanFormat(format),
        .subresourceRange = {.aspectMask = vk::ImageAspectFlagBits::eColor, .baseMipLevel = 0, .levelCount = 1,
            .baseArrayLayer = 0, .layerCount = 1}
    };

    auto imageView = vk::raii::ImageView(device, viewInfo);
    return std::make_unique<VulkanTexture>(std::move(image), std::move(memory), mapped, std::move(imageView));
}

vk::Format VulkanDevice::toVulkanFormat(const TextureFormat format) {
    auto vulkanFormat = vk::Format::eR8G8B8A8Unorm;
    switch (format) {
        case TextureFormat::RGBA8:
            vulkanFormat = vk::Format::eR8G8B8A8Unorm;
            break;
    }
    return vulkanFormat;
}

vk::ImageUsageFlags VulkanDevice::toVulkanImageUsageFlags(const TextureUsage usage) {
    vk::ImageUsageFlags vulkanUsage = {};
    const uint32_t usageBits = static_cast<uint32_t>(usage);

    if (usageBits & static_cast<uint32_t>(TextureUsage::RenderTarget)) {
        vulkanUsage |= vk::ImageUsageFlagBits::eColorAttachment;
    }
    if (usageBits & static_cast<uint32_t>(TextureUsage::DepthStencil)) {
        vulkanUsage |= vk::ImageUsageFlagBits::eDepthStencilAttachment;
    }
    if (usageBits & static_cast<uint32_t>(TextureUsage::ShaderResource)) {
        vulkanUsage |= vk::ImageUsageFlagBits::eSampled;
    }
    if (usageBits & static_cast<uint32_t>(TextureUsage::Storage)) {
        vulkanUsage |= vk::ImageUsageFlagBits::eStorage;
    }

    return vulkanUsage;
}

void VulkanDevice::createPhysicalDevice() {
    std::vector<vk::raii::PhysicalDevice> physicalDevices = context.getInstance().enumeratePhysicalDevices();

    auto const it = std::ranges::find_if(physicalDevices, [&](auto const & pD) {
        return isDeviceSuitable(pD, requiredDeviceExtensions);
    });

    if (it == physicalDevices.end()) {
        LOG_FATAL("failed to select vulkan physical device");
    }

    physicalDevice = *it;
}

uint32_t VulkanDevice::getQueueIndex(const vk::QueueFlagBits flags, const vk::raii::PhysicalDevice &physicalDevice) {
    const std::vector<vk::QueueFamilyProperties> = physicalDevice.getQueueFamilyProperties();

    uint32_t queueIndex = ~0;
    for (uint32_t i = 0; i < queueFamilyProperties.size(); i++) {
        if (queueFamilyProperties[i].queueFlags & flags) {
            queueIndex = i;
        }
    }
    return queueIndex;
}

// --- logical device ---
void VulkanDevice::createDevice(VulkanSurface& surface) {
    auto gQI = getQueuceIndex(vk::QueueFlagBits::eGraphics, physicalDevice);
    graphicsFamily = physicalDevice.getSurfaceSupportKHR(gQI, surface.getHandle()) ? gQI : ~0;

    if (graphicsFamily == ~0) {
        LOG_FATAL("failed to find a vulkan queue that supports graphics!");
    }

    vk::StructureChain<vk::PhysicalDeviceFeatures2,
        vk::PhysicalDeviceVulkan11Features,
        vk::PhysicalDeviceVulkan13Features,
        vk::PhysicalDeviceExtendedDynamicStateFeaturesEXT>
    featureChain = {
        {.features = {.samplerAnisotropy = true } },
        {.shaderDrawParameters = true},
        {.synchronization2 = true, .dynamicRendering = true},
        {.extendedDynamicState = true}
    };

    float queuePriority = 0.5;
    vk::DeviceQueueCreateInfo queueInfo{
        .queueFamilyIndex = graphicsFamily,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    vk::DeviceCreateInfo deviceCreateInfo{
        .pNext = &featureChain.get<vk::PhysicalDeviceFeatures2>(),
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueInfo,
        .enabledExtensionCount = static_cast<uint32_t>(requiredDeviceExtensions.size()),
        .ppEnabledExtensionNames = requiredDeviceExtensions.data()
    };
    device = vk::raii::Device(physicalDevice, deviceCreateInfo);
    graphicsQueue = vk::raii::Queue(device, graphicsFamily, 0);
}

}
