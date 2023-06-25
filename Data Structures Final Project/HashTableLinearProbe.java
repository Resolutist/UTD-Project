//package project4_cs3345; Commented out for ease of grading.

public class HashTableLinearProbe <K,V>
{
	//Holds the default table size.
	private int defaultSize = 3;
	//Holds the number of entries in the hash table.
	private int size = 0;
	
	//Class to create the array to represent HashTable
	private static class HashEntry<K,V>
	{
		K key;
		V value;
		//Lazy Deletion
		private boolean deleted;
		
		//Constructor
		public HashEntry(K key, V value)
		{
			this.key = key;
			this.value = value;
		}
	}
	
	//Set up hashtable to set it to the default size in the following constructor.
	private HashEntry <K, V> hashtable[];
	
	//Constructor to ensure that hashtable is not null. 
	public HashTableLinearProbe()
	{
		//Initialize hashtable.
		this.hashtable = new HashEntry[defaultSize];
	}
	//Function to insert entry.
	public Boolean insert(K key, V value)
	{
		int i = 0;
		//Throw error message if the key is invalid or null.
		if(key == null)
			throw new IllegalArgumentException("The key is either null or invalid.");
		
		if(size >= defaultSize)
			rehash();
		
		//Return false if a duplicate entry is found.
		for(i = getHashValue(key); hashtable[i] != null; i = (i + 1) % defaultSize)
		{
			if(hashtable[i].equals(key))
				return false;
		}
		
		//Initialize Entry.
		HashEntry<K, V> entry = new HashEntry<>(key, value);
		hashtable[i] = entry;
		
		//Increment the number of entries.
		size++;
		
		return true;
	}
	
	//Function to check if the key exists in the table.
	public V find(K key)
	{
		for(int i = getHashValue(key); hashtable[i] != null; i =(i + 1) % defaultSize)
		{
			if(hashtable[i].key.equals(key) && !hashtable[i].deleted)
				//If found, return the value of the key.
				return hashtable[i].value;
		}
		//Return null if not found.
		return null;
	}
	
	//This function performs lazy deletion by marking the entry as deleted.
	public Boolean delete(K key)
	{
		int i = getHashValue(key);
		
		//Return false if entry was not found in the hash table.
		if(hashtable[i] == null)
			return false;
		
		hashtable[i].deleted = true;
		
		//Decrement size for the deletion.
		size--;
		
		//Return true if successfully deleted.
		return true;
	}
	
	//Function for returning the hash value for the given key.
	public int getHashValue(K key)
	{
		//Return -1 if not found. 
		if(key == null || key.hashCode() == 0)
			return -1;
		
		return key.hashCode() % defaultSize;
	}
	
	@SuppressWarnings("unchecked") //For line 88, in order for the new table to conform.
	private void rehash()
	{
		//Array to double the hash table size.
		HashEntry<K, V> newTable[] = new HashEntry[2 * defaultSize];
		
		//Rehash everything to the new table
		for(int i = 0; i < defaultSize; i++)
		{
			//Ignore items that are marked as deleted.
			if(hashtable[i] != null && !hashtable[i].deleted)
				newTable[i] = hashtable[i];
		}
	}
	
}
