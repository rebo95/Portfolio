﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectPooler : MonoBehaviour
{

    // A class to create pools of different objects
    [System.Serializable]
    public class objectPoolItem
    {
        public string tag;
        public GameObject objectToPool;
        public int amountToPool;
    }


    // A list to store all of our different types of items
    public List<objectPoolItem> itemsToPool;

    // New dictionary set to be able to find a specific pool of objects
    public Dictionary<string, Queue<GameObject>> poolDictionary;

    // We make the pool a singleton to get access in an easy way
    public static ObjectPooler instance;

    private void Awake()
    {
        instance = this;
        
        // We create a new dictionary
        poolDictionary = new Dictionary<string, Queue<GameObject>>();

        foreach (objectPoolItem item in itemsToPool)
        {
            // We create a gameObject queue for each key of the dictionary
            Queue<GameObject> objectPool = new Queue<GameObject>();

            // We add the objects to the pools
            for (int i = 0; i < item.amountToPool; i++)
            {
                GameObject go = Instantiate(item.objectToPool);
                go.SetActive(false);
                objectPool.Enqueue(go);
            }

            // We add the pool to the dictionary
            poolDictionary.Add(item.tag, objectPool);
        }
    }

    // Method to get an item from one of the pools
    GameObject getItemFromPool(string tag)
    {
        // To prevent unexpected errors
        if (!poolDictionary.ContainsKey(tag))
        {
            Debug.LogWarning("GameObject with tag '" + tag + "' doesn't exist.");
            return null;
        }

        // We search the pool and select the first element
        GameObject objectToSpawn = poolDictionary[tag].Dequeue();

        // We add the element selected to the back to reuse it later
        poolDictionary[tag].Enqueue(objectToSpawn);

        return objectToSpawn;
    }

    // Method to spawn a gameObject from one of the pools
    public void spawnFromPool(string tag, Vector2 position, Quaternion rotation)
    {
        // We search the pool and give life to one of the objects
        GameObject obj = getItemFromPool(tag);
        obj.transform.position = position;
        obj.transform.rotation = rotation;
        obj.SetActive(true);

        // We call an specific method of an interface to make sure the start method of the reused objects works 
        IPooledObject pooledObj = obj.GetComponent<IPooledObject>();

        if (pooledObj != null)
            pooledObj.OnObjectSpawn();
    }

    // Method to spawn an specific object of the queue
    public void spawnSpecificFromPool(GameObject go, Vector2 position, Quaternion rotation)
    {
        go.transform.position = position;
        go.transform.rotation = rotation;
        go.SetActive(true);

        // We call an specific method of an interface to make sure the start method of the reused objects works 
        IPooledObject pooledObj = go.GetComponent<IPooledObject>();

        if (pooledObj != null)
            pooledObj.OnObjectSpawn();
    }

    // Method to disabled a gameObject form one of the pools
    public void killGameObject(GameObject obj)
    {
        obj.SetActive(false);
    }

    // Checks if there's a pool with an specific tag
    public bool itemExists(string tag)
    {
        bool b;

        if (poolDictionary.ContainsKey(tag))
            b = true;
        else
            b = false;

        return b;    
    }
}
