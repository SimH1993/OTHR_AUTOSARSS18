package generator.oil.model;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class Task {
    private String name;
    private Autostart autostart = Autostart.FALSE;
    //TODO - Priority default?
    private int priority = 100;
    private int activation = 1;
    private String schedule = "NON";
    //TODO - Redundant if variables work
    private int stackSize = 512;
    private List<Event> events = new ArrayList<>();

    public Task(String name) {
        this.name = Objects.requireNonNull(name);
    }

    public int getPriority() {
        return priority;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }

    public int getActivation() {
        return activation;
    }

    public void setActivation(int activation) {
        this.activation = activation;
    }

    public String getSchedule() {
        return schedule;
    }

    public void setSchedule(String schedule) {
        this.schedule = schedule;
    }

    public int getStackSize() {
        return stackSize;
    }

    public void setStackSize(int stackSize) {
        this.stackSize = stackSize;
    }

    public List<Event> getEvents() {
        return events;
    }

    public void setEvents(List<Event> events) {
        this.events = events;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Autostart getAutostart() {
        return autostart;
    }

    public void setAutostart(Autostart autostart) {
        this.autostart = autostart;
    }
}
