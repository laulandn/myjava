// This code from the Java in a Nutshell book...

import java.applet.*;
import java.awt.*;

public class scribble extends Applet {
  private int last_x=0;
  private int last_y=0;
  private Color current_color=Color.black;
  private Button clear_button;
  private Choice color_choices;
  //
  public void init() {
    //
    this.setBackground(Color.white);
    //
    clear_button=new Button("Clear");
    clear_button.setForeground(Color.black);
    clear_button.setBackground(Color.lightGray);
    this.add(clear_button);
    //
    color_choices=new Choice();
    color_choices.addItem("black");
    color_choices.addItem("red");
    color_choices.addItem("yellow");
    color_choices.addItem("green");
    color_choices.setForeground(Color.black);
    color_choices.setBackground(Color.lightGray);
    this.add(color_choices);
    //
  }
  //
  public boolean mouseDown(Event e,int x, int y)
  {
    last_x=x;  last_y=y;
    return true;
  }
  //
  public boolean mouseDrag(Event e,int x, int y)
  {
    Graphics g=this.getGraphics();
    g.setColor(current_color);
    g.drawLine(last_x,last_y,x,y);
    last_x=x;
    last_y=y;
    return true;
  }
  //
  public boolean action(Event event,Object arg)
  {
    if(event.target==clear_button) {
      Graphics g=this.getGraphics();
      Rectangle r=this.bounds();
      g.setColor(this.getBackground());
      g.fillRect(r.x,r.y,r.width,r.height);
      return true;
    }
    else if(event.target==color_choices) {
      if(arg.equals("black")) current_color=Color.black;
      else if(arg.equals("red")) current_color=Color.red;
      else if(arg.equals("yellow")) current_color=Color.yellow;
      else if(arg.equals("green")) current_color=Color.green;
      return true;
    }
    else return super.action(event,arg);
  }
}