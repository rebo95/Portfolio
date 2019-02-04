using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartLevelSpawner : MonoBehaviour {

    // A class to store the spawners and also add them from the editor
    [System.Serializable]
    public class itemsToSpawn
    {
        public string tag;
        public List<GameObject> spawners;
    }

    // A list with all the different objects that have to spawn at the beginning
    public List<itemsToSpawn> poolItemsToSpawn;

    // The size of the spawners' list
    int listSize;


	// Use this for initialization
	void Start ()
    {
        spawnItems();
    }


    void spawnItems()
    {
        foreach (itemsToSpawn item in poolItemsToSpawn)
        {
            if (ObjectPooler.instance.itemExists(item.tag))
            {
                listSize = item.spawners.Count;
                for (int i = 0; i < listSize; i++)
                {
                    Vector2 pos = item.spawners[i].transform.position;
                    Quaternion rot = item.spawners[i].transform.rotation;
                    ObjectPooler.instance.spawnFromPool(item.tag, pos, rot);
                }
                item.spawners.Clear();
            }
        }
    }


    private void OnValidate()
    {
        foreach (itemsToSpawn item in poolItemsToSpawn)
        {
            for (int i = 0; i < item.spawners.Count; i++)               
                if (item.spawners[i] == null)
                    item.spawners.RemoveAt(i);           
        }
    }

}
