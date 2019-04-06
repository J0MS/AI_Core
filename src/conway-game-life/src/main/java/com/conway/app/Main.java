package com.conway.app;
import java.util.*;
import javax.swing.*;

public class Main {
	private static int x;
	private static int y;
	private static int time;

	public static void main(String[] args) {
	y = 1500;
	x = 400;
	time = 100;

	String tTemp = "";


		int pregunta = JOptionPane.showConfirmDialog(null, "¿Desea insertar celdas inmunes iniciales?", "Bienvenido", JOptionPane.YES_NO_OPTION);
		tTemp = JOptionPane.showInputDialog("Inserte la velocidad de evolución (en milisegundos):","100");
		time = Integer.parseInt(tTemp);
			if (pregunta == 0) {
		    	GUI gui = new GUI(x,y);
	    		gui.GameTimer(time);
			}


	}
}
