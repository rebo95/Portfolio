
using UnityEngine;

[System.Serializable]
public class DialogColor_Class
{
    public string text;
    public enum WhoTalking
    {
        Anya, Brumund, Viraya
    }
    public WhoTalking talker = WhoTalking.Anya;
}


