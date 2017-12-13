/**
 * 
 */
package tests;

import java.util.Random;

import safes.Safe;
import safes.SafeWithCode;
import safes.ToSale;
import valuables.Emerald;
import valuables.Gemstone;
import valuables.Rubis;
import valuables.Saphir;

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

		Gemstone gem = new Emerald(10, 13.5);
		System.out.println("Poids : " + gem.getWeight());
		System.out.println("Valeur : " + gem.getValue());

		System.out.println("Expertisons cette pierre : " );
		gem.expertize();
		System.out.println("Valeur : " + gem.getValue());	

		Gemstone tabGems [] = new Gemstone[10];
		Random rd = new Random();
		for(int i = 0; i < tabGems.length; i++){
			tabGems[i] = new Rubis(rd.nextInt(10)+1, rd.nextInt(10)+1);
			tabGems[i].expertize();
			System.out.println("Gem " + i + " : " + tabGems[i].getValue());
		}

		Safe safe = new SafeWithCode(1234, 8);
		safe.addGem(gem);
		safe.open(1234);
		for(int i = 0 ; i < tabGems.length; i++){
			safe.addGem(tabGems[i]);
			System.out.println("Round " + i);
			System.out.println("\tWeight : " + safe.getWeight() +"\t Value: " + safe.getValue());
		}

		safe.addGem(tabGems[0]);
		
		
		ToSale ts = new Saphir(10, 20);
		ts = new Safe(20);
		
		System.out.println(ts.getValue());
	}

}
