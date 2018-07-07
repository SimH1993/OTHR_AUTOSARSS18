package generator.oil.model.alarm;

public class Alarm {
    private String name;
    private Action action;
    private AlarmAutostart autostart = AlarmAutostart.FALSE;

    public Alarm(String name, Action action) {
        this.name = name;
        this.action = action;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Action getAction() {
        return action;
    }

    public void setAction(Action action) {
        this.action = action;
    }

    public AlarmAutostart getAutostart() {
        return autostart;
    }

    public void setAutostart(AlarmAutostart autostart) {
        this.autostart = autostart;
    }
}
