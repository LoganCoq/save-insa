package simpleEquation;

public class TestEquation {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		OneDegreeEquation eq = new OneDegreeEquation(12, -5);
		
		System.out.println(eq);
		System.out.println(eq.isSolved());
		System.out.println(eq.getSolution());
		System.out.println(eq.isSolved());
		
		eq.setCoeffA(4);
		
		System.out.println(eq.isSolved());
		System.out.println(eq.getSolution());
		System.out.println(eq.isSolved());
				

	}

}
