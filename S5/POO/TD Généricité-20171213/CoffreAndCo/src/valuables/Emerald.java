/**
 * 
 */
package valuables;

/** 
 * @author pascal
 */
public class Emerald extends Gemstone {

	public Emerald(double weight, double volume) {
		super(weight, volume);
		// TODO Auto-generated constructor stub
	}


	/**
	 */
	public void expertize(){
		value = weight* volume * weight;
		
	}

}
