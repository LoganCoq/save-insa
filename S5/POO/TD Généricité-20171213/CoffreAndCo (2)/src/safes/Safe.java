/**
 * 
 */
package safes;

import java.util.ArrayList;

import valuables.Gemstone;

/**
 * A contener for Gems
 * @author  pascal
 */
public class Safe  {


	/**
	 * @uml.property  name="capacity"
	 */
	private final int capacity ;

	/** 
	 * @uml.property name="opened"
	 */
	private boolean opened;

	/**
	 * Places to store Gems
	 */
	private ArrayList<Gemstone> myContent;

	/**
	 * @uml.property  name="currentGemsNb"
	 */
	private int currentGemsNb ;

	/**
	 * Initialization of the safe. It is assumed that the safe is built empty, closed
	 * @param capacity number of places in the safe
	 */
	public Safe(int capacity) {
		this.capacity = capacity;
		myContent = new ArrayList<Gemstone>();
		opened = false;
		currentGemsNb = 0;
	}

	/** 
	 * @return  the opened
	 * @uml.property  name="opened"
	 */
	public boolean isOpened() {
		return opened;
	}



	public void open(int aDummyValue){

		opened = true;
	}

	public void close(){
		opened = false;
	}


	public boolean isEmpty(){
		return currentGemsNb == 0;
	}

	public boolean isFull(){
		return currentGemsNb == capacity;
	}


	/**
	 * @return  the capacity
	 * @uml.property  name="capacity"
	 */
	public int getCapacity() {
		return capacity;
	}

	/**
	 * @return  the currentGemsNb
	 * @uml.property  name="currentGemsNb"
	 */
	public int getCurrentGemsNb() {
		return currentGemsNb;
	}

	/**
	 * 
	 * @return the global value of the gems inside the safe
	 */
	public double getValue(){

		double val = 0;
		for(Gemstone g : myContent)
			val += g.getValue();

		return val;
	}

	/**
	 * 
	 * @param gem
	 * @return true if the process has successfully finished: the gem is in the safe
	 */
	public boolean addGem(Gemstone gem){
		// Testing when it is impossible to add the gem

		System.out.println("Trying to add a " + gem.getClass().getName());
		//1. The safe is closed
		if(!isOpened()) {
			System.err.println("Cannot add the gem: the safe is closed");
			return false;
		}

		//2. The gem is already  in a safe
		if(gem.getMySafe()!=null){
			System.err.println("Cannot add the gem: the gem is already in a safe (maybe this one!)");
			return false;
		}

		//3. No room left
		if(isFull()){
			System.err.println("Cannot add the gem: the safe is full");
			return false;
		}



		// We can add the gem in the other cases.

		myContent.add(gem);
		currentGemsNb ++;
		return true;

	}

	public Gemstone removeGem(){
		Gemstone gem = null;
		// Testing when we cannot remove a Gem
		//1. The safe is closed
		if(!isOpened()) {
			System.err.println("Cannot remove any gem: the safe is closed");
			return null	;
		}

		//2. The safe is empty
		if(isEmpty()){
			System.err.println("Cannot remove any gem: the safe is empty");
			return null;
		}

		gem = myContent.remove(0);
		currentGemsNb --;


		return gem;
	}

	/** 
	 * Setter of the property <tt>opened</tt>
	 * @param opened  The opened to set.
	 * @uml.property  name="opened"
	 */
	public void setOpened(boolean opened) {
		this.opened = opened;
	}

}

