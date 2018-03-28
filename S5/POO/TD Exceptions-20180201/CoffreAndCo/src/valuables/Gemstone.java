package valuables;

import safes.Safe;



/**
 * @author  pascal
 * @version  1.0
 */
public abstract class Gemstone {
	
	/**
	 * @uml.property  name="value"
	 */
	protected double value;
	/**
	 * @uml.property  name="volume"
	 */

	protected final double volume;
	
	/**
	 * @param volume
	 */
	public Gemstone(double volume) {

		this.volume = volume;
		
	}

	/**
	 * @return  the value
	 * @uml.property  name="value"
	 */
	public double getValue() {
		return value;
	}


	/**
	 * @return  the volume
	 * @uml.property  name="volume"
	 */
	public double getVolume() {
		return volume;
	}
	
	
	public abstract void expertize();
	/*
	{
		value = weight * volume * Math.PI;
	}
	*/
	
	
	// Connection with a safe
	/**
	 * @uml.property  name="mySafe"
	 * @uml.associationEnd  
	 */
	private Safe mySafe;

	/**
	 * @return  the mySafe
	 * @uml.property  name="mySafe"
	 */
	public Safe getMySafe() {
		return mySafe;
	}

	/**
	 * @param mySafe  the mySafe to set
	 * @uml.property  name="mySafe"
	 */
	public void setMySafe(Safe mySafe) {
		this.mySafe = mySafe;
	}

}
