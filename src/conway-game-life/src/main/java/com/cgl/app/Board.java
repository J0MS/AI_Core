package com.outbreaksimulator.app;

import javax.swing.JPanel;
import java.awt.*;
import java.applet.Applet;
import java.awt.Color;
import java.awt.Graphics;

public class Board extends JPanel {

	private int[][] cellArray;
	private int x;
	private int y;

	public Board(int x, int y, int[][] cellArray) {
		this.cellArray = cellArray;
		this.x = x/5;
		this.y = y/5;

		JPanel boardPanel = new JPanel();
		boardPanel.setLayout(null);
		boardPanel.setPreferredSize(new Dimension(x,y));
	}

	public void paintComponent(Graphics g) {

		for (int i = 0; i < this.x; i++) {
			for (int j = 0; j < this.y; j++) {
			Color customColor = new Color(94,75,54);

				if (cellArray[i][j] == 1) {
					g.setColor(customColor);
				}

				if (cellArray[i][j] == 2) {
					g.setColor(customColor);
				}

				if (cellArray[i][j] == 3) {
					g.setColor(customColor);
				}

				if (cellArray[i][j] == 4) {
					g.setColor(Color.white.brighter());
				}

				if (cellArray[i][j] == 5) {
					g.setColor((Color.white).darker().darker());
				}

				if (cellArray[i][j] == 6) {
					g.setColor(Color.blue);
				}

				if (cellArray[i][j] == 0) {
					g.setColor((Color.blue).darker().darker());
				}

				g.fill3DRect(j*5, i*5, 5,5, true);
			}
		}

		repaint();

	}
}
