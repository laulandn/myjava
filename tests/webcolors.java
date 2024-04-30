// This code from the Java Game Programming for Dummies book...

import java.awt.*;
import java.applet.Applet;

public class webcolors extends Applet {
	private int[]    comp = { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF};

	public void paint (Graphics g) {
		int width = getSize().width;
		int height = getSize().height;
		int columns = 6;
		int rows = 6 * 6;
		int cellWidth = width / columns;
		int cellHeight = height / rows;
		int hGap = (width - (columns * cellWidth)) / 2;
		int vGap = (height - (rows * cellHeight)) / 2;
		for (int rr = 0; rr < rows; rr++) {
			for (int cc = 0; cc < columns; cc++) {
				int red = comp[rr / 6];
				int grn = comp[rr % 6];
				int blu = comp[cc];
				g.setColor(new Color(red, grn, blu));
				g.fillRect((cc * cellWidth) + hGap, (rr * cellHeight) + vGap,
				           cellWidth, cellHeight);
			}
		}
	}
}
