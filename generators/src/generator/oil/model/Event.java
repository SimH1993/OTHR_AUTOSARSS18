package generator.oil.model;

import java.util.Objects;

public class Event {
    private String name;
    private String mask = "AUTO";

    public Event(String name) {
        this.name = Objects.requireNonNull(name);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getMask() {
        return mask;
    }

    public void setMask(String mask) {
        this.mask = mask;
    }
}
