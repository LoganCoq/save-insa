/**
 * 
 */
package tests;

import java.util.Random;

import safes.Safe;
import safes.SafeWithCode;
import valuables.Emerald;
import valuables.Gemstone;
import valuables.Rubis;


/**
 * @author pascal
 *
 */
public class FirstTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Gemstone gem = new Emerald( 13.5);
		System.out.println("Poids : " + gem.getVolume());
		System.out.println("Valeur : " + gem.getValue());

		System.out.println("Expertisons cette pierre : " );
		gem.expertize();
		System.out.println("Valeur : " + gem.getValue());	

		Gemstone tabGems [] = new Gemstone[10];
		Random rd = new Random();
		for(int i = 0; i < tabGems.length; i++){
			tabGems[i] = new Rubis(rd.nextInt(10)+1);
			tabGems[i].expertize();
			System.out.println("Gem " + i + " : " + tabGems[i].getValue());
		}

		Safe safe = new SafeWithCode(1234, 8);
		safe.addGem(gem);
		safe.open(1234);
		for(int i = 0 ; i < tabGems.length; i++){
			safe.addGem(tabGems[i]);
			System.out.println("Round " + i);
			System.out.println("\t Value: " + safe.getValue());
		}

		safe.addGem(tabGems[0]);
		
		

	}

}
