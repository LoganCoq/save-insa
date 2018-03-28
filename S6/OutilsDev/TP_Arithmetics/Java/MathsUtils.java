package johnArithmetics;

/**
 * 
 * My vision of maths, by John, Another dev.
 * 
 * @author John
 *
 */
public class MathsUtils {
	/**
	 * 
	 * John's optimized PPCM version
	 * 
	 * @param a
	 *            one value
	 * @param b
	 *            another value
	 * @return ppcm
	 */
	public static int johnBetterPPCM(int a, int b) {
		int sum, modulo, PPCM;

		sum = a * b;
		modulo = a % b;
		while (modulo != 0) {
			a = b;
			b = modulo;
			modulo = a % b;
		}
		PPCM = sum / b;
		return PPCM;
	}

	/**
	 * 
	 * John's faulty PPCM version. I can't figure out if it's working or not.
	 * 
	 * @param a
	 *            one value
	 * @param b
	 *            another value
	 * @return ppcm
	 */
	public static int johnFaultyPPCM(int a, int b) {
		int p, mincm = 0;
		p = a * b;
		while ((p > a) && (p > b)) {
			if ((p % a == 0) && (p % b == 0)) {
				mincm = p;
			}
			p = p - 1;
		}
		return mincm;
	}

	/**
	 * 
	 * John's correct PPCM version. Someone came and add a few line to correct a
	 * bug in my code. Not sure if he's right or wrong.
	 * 
	 * @param a
	 *            one value
	 * @param b
	 *            another value
	 * @return ppcm
	 */
	public static int johnCorrectPPCM(int a, int b) {
		int p, mincm = 0;
		p = a * b;
		if (a == b)
			return a;

		while ((p > a) && (p > b)) {
			if ((p % a == 0) && (p % b == 0)) {
				mincm = p;
			}
			p = p - 1;
		}
		return mincm;
	}
}
