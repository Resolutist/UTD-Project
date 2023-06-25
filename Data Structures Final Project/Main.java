//package project4_cs3345; Commented out for ease of grading.

import java.util.*;

public class Main 
{
	//This method calls the functions from HashTableLinearProbe.
	public static void main(String args[])
	{
		//Check with String object.
		HashTableLinearProbe<String, String> strTable = new HashTableLinearProbe<>();
		//Check with Integer object.
		HashTableLinearProbe<Integer, Integer> intTable = new HashTableLinearProbe<>();
		
		//Test Insert Function with both objects.
		strTable.insert("Kyle", " White");
		intTable.insert(1, 100);
		
		//Test find function with both objects.
		System.out.println("Find Kyle" + strTable.find("Kyle"));
		System.out.println("Find 1" + intTable.find(1));
		
		//Test delete function with both objects.
		System.out.println("Delete Kyle \n" + strTable.delete("Kyle"));
		System.out.println("Delete 1 \n" + intTable.delete(1));
		
		//Test rehash function with both objects.
		System.out.println(strTable.getHashValue("Kyle"));
		System.out.println(intTable.getHashValue(1));
	}
}
