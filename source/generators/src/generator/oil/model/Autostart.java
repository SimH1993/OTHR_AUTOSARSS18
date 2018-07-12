package generator.oil.model;

public class Autostart {
    private String appMode = Constants.defaultAppmode;
    public static final Autostart FALSE = new Autostart() {
        @Override
        public String toString() {
            return "FALSE";
        }
    };

    public static final Autostart TRUE = new Autostart() {
        @Override
        public String toString() {
            return "TRUE { APPMODE = " + getAppMode() + "; }";
        }
    };

    protected Autostart() {
    }

    public String getAppMode() {
        return appMode;
    }

    public void setAppMode(String appMode) {
        this.appMode = appMode;
    }

    @Override
    public String toString() {
        throw new RuntimeException("ToString() of class Autostart must be overloaded");
    }
}
