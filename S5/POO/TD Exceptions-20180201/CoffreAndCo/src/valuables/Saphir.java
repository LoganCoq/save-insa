/**
 * 
 */
package valuables;

/** 
 * @author pascal
 */
public final class Saphir extends Gemstone {

	/**
	 * @param weight
	 * @param volume
	 */
	public Saphir(double volume) {
		super( volume);
		// TODO Auto-generated constructor stub
	}

	/* (non-Javadoc)
	 * @see valuables.Gemstone#expertize()
	 */
	@Override
	public void expertize() {
		// TODO Auto-generated method stub
		value = 1000+volume;

	}

}
