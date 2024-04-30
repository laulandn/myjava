// This code from the Java Game Programming for Dummies book...

import java.awt.*;
import java.applet.Applet;
import java.util.*;

class ball {
	public float    x, y, dx, dy;
	private Color   color;
	private int     size;
	
	ball (float x, float y, float dx, float dy, int size, Color color) {
		this.x = x;
		this.y = y;
		this.dx = dx;
		this.dy = dy;
		this.color = color;
		this.size = size;
	}
	
	public void move (Rectangle bounds) {
		// Add velocity values dx/dy to position to get
		// ball's new position
		x += dx;
		y += dy;
		// Check for collision with left edge
		if (x < bounds.x && dx < 0) {
			dx = -dx;
			x -= 2 * (x - bounds.x);
		}
		// Check for collision with right edge
		else if ((x + size) > (bounds.x + bounds.width) && dx > 0) {
			dx = -dx;
			x -= 2 * ((x + size) - (bounds.x + bounds.width));
		}
		// Check for collision with top edge
		if (y < bounds.y && dy < 0) {
			dy = -dy;
			y -= 2 * (y - bounds.y);
		}
		// Check for collision with bottom edge
		else if ((y + size) > (bounds.y + bounds.height) && dy > 0) {
			dy = -dy;
			y -= 2 * ((y + size) - (bounds.y + bounds.height));
		}
	}
	
	public void draw (Graphics g) {
		g.setColor(color);
		g.fillOval((int) x, (int) y, size, size);
	}
}

public class bounce extends Applet implements Runnable {
	private Image       offscreenImage;
	private Graphics    offscr;
	private Thread      ticker;
	private boolean     running = false;
	private	Rectangle   bounds;
	private ball        ball;
	private int         width, height;

	public void init() {
		width = size().width;
		height = size().height;
		bounds = new Rectangle(width, height);
        // Initialize Ball's position and velocity
		ball = new ball(width / 3.0f, height / 4.0f, 1.5f,
		                2.3f, 12,
                        Color.blue);
	}
	
	public void run () {
		while (running) {
			repaint(); 
			try {
				ticker.sleep(1000 / 30);
			} catch (InterruptedException e) { ; }
		}
	}
	
	public void paint (Graphics g) {
		if (offscr == null) {
			offscreenImage = createImage(width, height);
			offscr = offscreenImage.getGraphics();
		}
		// Draw checkerboard background
		int x2 = width >> 1;
		int y2 = height >> 1;
		offscr.setColor(Color.gray);
		offscr.fillRect(0, 0, x2, y2);
		offscr.fillRect(x2, y2, width - x2, height - y2);
		offscr.setColor(Color.white);
		offscr.fillRect(x2, 0, width - x2, height - y2);
		offscr.fillRect(0, y2, x2, y2);
		ball.move(bounds);
		ball.draw(offscr);
		g.drawImage(offscreenImage, 0, 0, null);
	}

	public void update (Graphics g) {
		paint(g);
	}
	
	public synchronized void start () {
		if (ticker == null  ||  !ticker.isAlive()) {
			running = true;
			ticker = new Thread(this);
			ticker.setPriority(Thread.MIN_PRIORITY + 1);
			ticker.start();
		}
	}
	
	public synchronized void stop () {
		running = false;
	}
}
