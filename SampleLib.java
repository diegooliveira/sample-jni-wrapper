

public class SampleLib {

    static {
	     System.loadLibrary("MyWrapper");
    }

    public native int soma(int a, int b);

}
