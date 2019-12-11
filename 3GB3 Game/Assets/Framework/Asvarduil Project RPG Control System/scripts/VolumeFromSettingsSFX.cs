using UnityEngine;
using System.Collections;

public class VolumeFromSettingsSFX : MonoBehaviour 
{
	public void Awake() 
	{
		GetComponent<AudioSource>().volume = Settings.sfxVolume;
	}

	public void Update() 
	{
		GetComponent<AudioSource>().volume = Settings.sfxVolume;
	}
}
