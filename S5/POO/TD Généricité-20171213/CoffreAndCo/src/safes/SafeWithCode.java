/**
 * 
 */
package safes;

/** 
 * @author pascal
 */
public class SafeWithCode extends Safe {

	/**
	 * @uml.property  name="code" readOnly="true"
	 */
	private int code;


	/**
	 */
	public SafeWithCode(int unCode, int capacity){
		super(capacity);
		code = unCode;
	}



	/**
	 */
	public void open(int aTestCode){

		if(aTestCode!=code){
			System.err.println("Cannot Open Safe : Wrong Code");
		}
		else
		{
			super.open(aTestCode);
			//opened = true;
		}

	}

}
