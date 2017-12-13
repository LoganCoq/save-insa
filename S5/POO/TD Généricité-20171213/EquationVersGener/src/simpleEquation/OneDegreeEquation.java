/**
 * Une équation de degré un de type aX+b = 0,  avec a et b des float.
 */

package simpleEquation;

/**
 * @author  pascal
 */
public class OneDegreeEquation {

	/**
	 * @return  the coeffA
	 * @uml.property  name="coeffA"
	 */
	public float getCoeffA() {
		return coeffA;
	}

	/**
	 * @param coeffA  the coeffA to set
	 * @uml.property  name="coeffA"
	 */
	public void setCoeffA(float coeffA) {
		this.coeffA = coeffA;
		solved = false;
	}

	/**
	 * @return  the coeffB
	 * @uml.property  name="coeffB"
	 */
	public float getCoeffB() {
		return coeffB;
	}

	/**
	 * @param coeffB  the coeffB to set
	 * @uml.property  name="coeffB"
	 */
	public void setCoeffB(float coeffB) {
		solved = false;
		this.coeffB = coeffB;
	}

	/**
	 * @return  the solved
	 * @uml.property  name="solved"
	 */
	public boolean isSolved() {
		return solved;
	}

	/**
	 * @return  the solution
	 * @uml.property  name="solution"
	 */
	public float getSolution() {
		solve();  // Discutable si on pense qu'un getter ne modifie pas l'objet.
		return solution;
	}

	/**
	 * @uml.property  name="coeffA"
	 */
	private float coeffA;
	/**
	 * @uml.property  name="coeffB"
	 */
	private float coeffB;
	
	/**
	 * @uml.property  name="solved"
	 */
	private boolean solved;
	
	/**
	 * @uml.property  name="solution"
	 */
	private float solution;

	/**
	 * @param coeffA
	 * @param coeffB
	 */
	public OneDegreeEquation(float coeffA, float coeffB) {
		this.coeffA = coeffA;
		this.coeffB = coeffB;
		
		solution = 0;
		solved = false;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "Equation : " + coeffA + " X + " + coeffB + " = 0";
	}
	
	public void solve(){
		if(!solved){
			solved  = true;
			solution = -coeffB / coeffA;
		}
		
	}
	
	
	
	
}
