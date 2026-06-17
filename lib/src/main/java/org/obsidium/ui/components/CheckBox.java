package org.obsidium.ui.components;

import org.obsidium.graphics.surface.ExtendableSurface;
import org.obsidium.graphics.surface.SimpleSurface;
import org.obsidium.math.Vector2;

public abstract class CheckBox extends Component {
    protected boolean checked = false;

    public boolean isChecked() {
        return checked;
    }

    public void setChecked(boolean checked) {
        if (this.checked != checked) {
            this.checked = checked;
            invalidate();
        }
    }
}
