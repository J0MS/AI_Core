package com.outbreaksimulator.app;

import java.util.Random;

public class Cells {

	private int[] surroundingCells = new int[9];
	private int cellState;

	public Cells(int[] surroundingCells) {
		this.surroundingCells = surroundingCells;
		cellState = this.surroundingCells[4];

		Random rand = new Random();


switch (cellState) {


			//Fire
			case 1: {
				for (int i : this.surroundingCells) {
					if (i == 6) {//
						i = 3;//
						cellState = 3;//
					}

					if (i != 6) {//6
						if (rand.nextInt(3) == 1) {//3,0
							cellState = 3;//2
						} else {
							cellState = 1;//1
						}
					}
				}
				break;
			}

			//Ash
			case 2: {
				if (rand.nextInt(100) == 0) {
					cellState = 2;
				} else {
					cellState = 3;
				}
				break;
			}

			//Ground
			case 3: {
				if (rand.nextInt(200) == 0) {
					if (rand.nextInt(5) == 0) {
						cellState = 5;//5
					} else {
						cellState = 3;//4
					}
				} else {
					cellState = 3;//3
				}
				break;
			}

			//Tree
			case 4: {
				for (int i : this.surroundingCells) {
					if (i == 1) {
						if (rand.nextInt(3) == 0) {
							cellState = 1;
						} else {
							cellState = 4;
						}
					}
				}

				if (rand.nextInt(100000) == 0) {
					cellState = 1;
				}

				break;
			}

			case 5: {
				for (int i : this.surroundingCells) {
					if (i == 1) {
						if (rand.nextInt(10) == 0) {
							cellState = 1;
						} else {
							cellState = 5;
						}
					}
				}

				if (rand.nextInt(100000) == 0) {
					cellState = 1;
				}

				break;
			}

		}

		this.surroundingCells[4] = cellState;
	}

	public int[] returnCells() {
		return this.surroundingCells;
	}

}
