package com.conway.app;

import java.awt.event.*;
import javax.swing.*;
import java.util.Random;
import java.util.TimerTask;
import java.util.Timer;


public class GUI extends JFrame implements MouseMotionListener, MouseListener {

	private boolean dragging;
	private int[][] cellArray;
	private int xNew;
	private int yNew;
	private int[] temporaryCells = new int[19];
	private int[] newCells = new int[9];

	private int leftClickX = -10;
	private int leftClickY = -10;
	private int rightClickX = -10;
	private int rightClickY = -10;

	public GUI(int xSize, int ySize) {
		super("Modelo de Propagación de Epidemia");
		super.frameInit();
		makeCells(xSize,ySize);
		//printCells(cellArray);
		setLayout(null);
		setContentPane(new Board(xSize, ySize,cellArray));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
		setVisible(true);
		setResizable(true);
		setDefaultLookAndFeelDecorated(true);
		setSize(ySize,xSize+22);
		addMouseListener(this);
		addMouseMotionListener(this);

		xNew = xSize/5;
		yNew = ySize/5;
	}

	public void drawCells() {
		for (int i = 0; i < xNew; i++) {
			for (int j = 0; j < yNew; j++) {

				int tempNumPlus = 0;

				for (int iX = -1; iX <= 1; iX++) {
					for (int jX = -1; jX <= 1; jX++) {

						int xValue = i+iX;
						int yValue = j+jX;

						if (xValue == -1) {
							xValue = xNew-1;
						} else if (xValue == xNew) {
							xValue = 0;
						}

						if (yValue == -1) {
							yValue = yNew-1;
						} else if (yValue == yNew) {
							yValue = 0;
						}

						temporaryCells[tempNumPlus] = cellArray[xValue][yValue];
						tempNumPlus++;

					}
				}

				Cells myCells = new Cells(temporaryCells);
				newCells = myCells.returnCells();

				for (int iY = -1; iY <= 1; iY++) {
					for (int jY = -1; jY <= 1; jY++) {

						int xValue = i+iY;
						int yValue = j+jY;

						if (xValue == -1) {
							xValue = xNew-1;
						} else if (xValue == xNew) {
							xValue = 0;
						}

						if (yValue == -1) {
							yValue = yNew-1;
						} else if (yValue == yNew) {
							yValue = 0;
						}

						cellArray[xValue][yValue] = newCells[(iY+1)*3+(jY+1)];
					}
				}
			}
		}

		if (leftClickY == -10 && leftClickX == -10) {

		} else {
			if (leftClickY >= xNew) {
				leftClickY = xNew-1;
			} else if (leftClickY <= 0) {
				leftClickY = 0;
			}

			if (leftClickX >= yNew) {
				leftClickX = yNew-1;
			} else if (leftClickX <= 0) {
				leftClickX = 0;
			}

			cellArray[leftClickY][leftClickX] = 0;
		}

		if (rightClickY == -10 && rightClickX == -10) {

		} else {
			if (rightClickY >= xNew) {
				rightClickY = xNew-1;
			} else if (rightClickY <= 0) {
				rightClickY = 0;
			}

			if (rightClickX >= yNew) {
				rightClickX = yNew-1;
			} else if (rightClickX <= 0) {
				rightClickX = 0;
			}

			cellArray[rightClickY][rightClickX] = 6;
		}
	}

	public void GameTimer(int zeit) {
		TimerTask task = new TimerTask() {
			public void run() {
				drawCells();
			}
		};
		Timer timer = new Timer();
		timer.schedule(task,0,zeit);
	}

	public void makeCells(int arrayX, int arrayY) {

		Random rand = new Random();

		int tempX = arrayX/5;
		int tempY = arrayY/5;

		cellArray = new int[tempX][tempY];

		for (int i = 0; i < tempX; i++) {
			for (int j = 0; j < tempY; j++) {
				cellArray[i][j] = rand.nextInt(2)+4;
			}
		}
	}

	public void printCells(int[][] myArray) {
		for (int[] array1D : myArray) {
			System.out.println();
			for (int i : array1D) {
				System.out.print(i + " ");
			}
		}
	}

	public void mousePressed(MouseEvent e) {
		if (e.getButton() == MouseEvent.BUTTON1) {
			leftClickX = (e.getX()/5-1);
			leftClickY = (e.getY()/5-1);
			dragging = true;

		} //else if (e.getButton() == MouseEvent.BUTTON3) {
			//rightClickX = (e.getX()/5-1);
			//rightClickY = (e.getY()/5-1);
			//dragging = false;

		//}
	}

	public void mouseDragged(MouseEvent e) {
		if (dragging) {
			leftClickX = (e.getX()/5-1);
			leftClickY = (e.getY()/5-5);
		} else if (!dragging) {
			rightClickX = (e.getX()/5-1);
			rightClickY = (e.getY()/5-5);
		}
	}

	public void mouseReleased(MouseEvent e) {}
	public void mouseClicked(MouseEvent e) {}
	public void mouseEntered(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
	public void mouseMoved(MouseEvent e) {}


	public void processWindowEvent(WindowEvent e) {
		if (e.getID() == WindowEvent.WINDOW_CLOSING) {
			JOptionPane.showMessageDialog(null, "Simulación finalizada");
			this.dispose();
			System.exit(0);
		}
	}

}
