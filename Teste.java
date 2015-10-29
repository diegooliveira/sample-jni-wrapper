
public class Teste {

	public static void main(String args[]){
		SampleLib sl = new SampleLib();
		try {
			System.out.println(sl.soma(Integer.parseInt(args[0]), 4));
		}catch(Exception e){
			System.out.println(e);
		}
	}

}
