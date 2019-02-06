using UnityEngine;
using System.Collections;

public class MovimientoCerveza : MonoBehaviour {

	public float Velx, direccion;//se declaran las variables publicas para poder cambiarlas en el editor y ver si hace falta hacerlas ir más despacio o más deprisa


	// Update is called once per frame
	void Update () {
		transform.Translate (//es el movimiento tipico del movimiento horizontal
			new Vector3 (Velx * direccion * Time.deltaTime, 0.0f, 0.0f)
		);

	}
}
