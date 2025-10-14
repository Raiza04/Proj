import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;
import javax.swing.*;
import javax.swing.border.LineBorder;

public class Calculator {
    int windowWidth = 360;
    int windowHeight = 540;

    Color customLightGrey = new Color (212, 212, 210);
    Color customDarkGrey = new Color (80, 80, 80);
    Color customBlack = new Color (28,28,28);
    Color customOrange = new Color (255, 149, 0);

    JFrame frame = new JFrame("Calculator");

    Calculator(){
        frame.setVisible(true);
        frame.setSize(windowWidth, windowHeight);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());
    }
}
