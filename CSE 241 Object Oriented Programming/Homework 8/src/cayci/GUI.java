package cayci;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

/**
 *
 * @author Cagri Cayci
 */
public class GUI implements PegSolitaireGame, Cloneable{
    /**
     * Keeps the size of the board.
     */
    private int size;
    /**
     * Keeps score, it is set 43 for initial board position. 
     */
    private int score = 43;
    /**
     * Keeps the type of the board.
     */
    private int currentType;
    /**
     * Keeps previous positiion of board as a 2D String array.
    */
    private String[][] previousBoard = null;
    /**
     * Keeps initial position of board as a 2D String array.
     */
    private String[][] initialBoard = null;
    /**
     * Keeps the board as a 2D JButton array.
     */
    private JButton[][] board;
    /**
     * JPanel for board.
     */
    private JPanel table;
    /**
     * JPanel for settings.
     */
    private JPanel settings;
    /**
     * Shows score as a JTextField.
     */
    private final JTextField scoreText = new JTextField("Score: " + score);
    /**
     * Main frame.
     */
    private final JFrame window;
    /**
     * Constructor, set everything for game.
     */
    public GUI(){
        window = new JFrame("Peg Solitaire");
        window.setLayout(new GridLayout());
        StringtoButton(first_type());
        table = tablePanel();
        settings = settingsPanel();
        window.add(settings);
        window.add(table);
        window.setSize(800, 800);
        window.setVisible(true);
        window.setLocationRelativeTo(null);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    /**
     * Clone method for GUI class.
     * @return GUI object.
     */
    public GUI clone() throws CloneNotSupportedException{
        GUI objClone = null;
        try{
            objClone = (GUI) super.clone();
        }
        catch(CloneNotSupportedException exception){
            System.out.println("ERROR!");
        }
        return objClone;
        
    }
    @Override
    public JButton undoButton(){
        var undo = new JButton("UNDO");
        ActionListener undoListener = new ActionListener(){
            public void actionPerformed(ActionEvent click){
                if(previousBoard != null){
                    table.setVisible(false);
                    window.remove(table);
                    StringtoButton(previousBoard);
                    table = tablePanel();
                    table.setVisible(true);
                    window.add(table);
                    previousBoard = null;
                    updateScore();
                }
            }
        };
        undo.addActionListener(undoListener);
        return undo;
    }
    @Override
    public JButton resetButton(){
        var reset = new JButton("RESET");
        ActionListener resetListener = new ActionListener(){
            public void actionPerformed(ActionEvent click){
                table.setVisible(false);
                window.remove(table);
                StringtoButton(initialBoard);
                table = tablePanel();
                table.setVisible(true);
                window.add(table);
                previousBoard = null;
                updateScore();
            }
        };
        reset.addActionListener(resetListener);
        return reset;
    }
    @Override
    public JButton saveButton(){
        var save = new JButton("SAVE");
        ActionListener saveListener = new ActionListener(){
            public void actionPerformed(ActionEvent click){
                try{
                    FileWriter writer = new FileWriter("record.txt");
                    String[][] virtualBoard = ButtontoString();
                    writer.write((size) + "\n" );
                    for(int i = 0; i < size; i++){
                        for(int j = 0; j < size; j++){
                            writer.write(virtualBoard[i][j] + ' ');
                        }
                        writer.write("\n");
                    }
                    writer.close();
                }
                catch(IOException e){
                   System.out.println("ERROR");
                }
            }
        };
        save.addActionListener(saveListener);
        return save;
    }
    @Override
    public JButton loadButton(){
        var load = new JButton("LOAD");
        ActionListener loadListener = new ActionListener(){
          public void actionPerformed(ActionEvent click){
                try{
                    FileReader reader = new FileReader("record.txt");
                    Scanner filereader = new Scanner(reader);
                    size = filereader.nextInt();
                    String[][] virtualBoard = new String[size][size];
                    for(int i = 0; i < size; i++){
                        for(int j = 0; j < size; j++){
                            virtualBoard[i][j] = filereader.next();
                        }
                    }
                    reader.close();
                    table.setVisible(false);
                    window.remove(table);
                    StringtoButton(virtualBoard);
                    table = tablePanel();
                    table.setVisible(true);
                    window.add(table);
                    previousBoard = null;
                    initialBoard = virtualBoard;
                    updateScore();
                }
                catch(IOException e){
                    System.out.println("ERROR");
                }
              
          }  
        };
        load.addActionListener(loadListener);
        return load;
    }
    @Override
    public JButton playAutoButton(){
        JButton playAuto = new JButton("PLAY AUTO");
        ActionListener playAutoListener = new ActionListener(){
            public void actionPerformed(ActionEvent click){
                autoPlay();
            }
        };
        playAuto.addActionListener(playAutoListener);
        return playAuto;
    }
    @Override
    public JButton playAutoAllButton(){
        JButton playAutoAll = new JButton("PLAY AUTO ALL");
        ActionListener playAutoAlllistener = new ActionListener(){
            public void actionPerformed(ActionEvent click){
                while(autoPlay()){
                }
            }
        };
        playAutoAll.addActionListener(playAutoAlllistener);
        return playAutoAll;
    }
    @Override
    public JRadioButton[] typeButtons(){
        JRadioButton[] types = new JRadioButton[5];
        ActionListener radioListener = new ActionListener(){
            public void actionPerformed(ActionEvent click){
                int index = 0; 
                table.setVisible(false);
                window.remove(table);
                for(int i = 0; i < 5; i++){
                    if(types[i] == click.getSource()){
                        index = i;
                        types[i].setSelected(true);
                    }
                    else{
                        types[i].setSelected(false);
                    }
                }
                switch(types[index].getText()){
                    case "Type 1":
                        currentType = 1;
                        break;
                    case "Type 2":
                        currentType = 2;
                        break;
                    case "Type 3":
                        currentType = 3;
                        break;
                    case "Type 4":
                        currentType = 4;
                        break;
                    case "Type 5":
                        currentType = 5;
                        break;
                }
                changeType();
                updateScore();
                previousBoard = null;
                table = tablePanel();
                table.setVisible(true);
                window.add(table);
                window.repaint();    
            }
        };
        for(int i = 0; i < 5; i++){
            types[i] = new JRadioButton("Type " + (i + 1));
            types[i].addActionListener(radioListener);
        }
        return types;
    }
    @Override
    public final JPanel tablePanel(){
        JPanel boardPanel = new JPanel();
        boardPanel.setLayout(new GridLayout(size, size));
        ActionListener boardListener = new ActionListener(){
            public void actionPerformed(ActionEvent click){
                int currentCoorX = 0, currentCoorY = 0, lastCoorX = 0, lastCoorY = 0, stepRank = 0;
                for(int i = 0; i < size; i++){
                    for(int j = 0; j < size; j++){
                        if(board[i][j].getBackground() == Color.yellow){
                            stepRank++;
                            lastCoorX = i;
                            lastCoorY = j;
                        }
                        if(board[i][j] == click.getSource()){
                            currentCoorX = i;
                            currentCoorY = j;
                        }
                    }
                }
                if(board[currentCoorX][currentCoorY].getBackground() == Color.green){
                    board[currentCoorX][currentCoorY].setBackground(Color.yellow);
                }
                if(stepRank == 1){
                    boolean success = userPlay(lastCoorX, lastCoorY, currentCoorX, currentCoorY);
                    if(success == false){
                        board[lastCoorX][lastCoorY].setBackground(Color.green);
                    }
                }
            }
        };
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                board[i][j].addActionListener(boardListener);
                boardPanel.add(board[i][j]); 
            }
        }
        return boardPanel;
    }
    @Override
    public final JPanel settingsPanel(){
        settings = new JPanel();
        var radioButtons = typeButtons();
        settings.setLayout(new GridLayout(4,3));
        settings.add(undoButton());
        settings.add(saveButton());
        settings.add(loadButton());
        settings.add(resetButton());
        settings.add(playAutoButton());
        settings.add(playAutoAllButton());
        for(int i = 0; i < 5; i++){
            settings.add(radioButtons[i]);
        }
        settings.add(scoreText);
        return settings;
    }
    @Override
    public ArrayList<Integer> emptyCoor(){
        var emptycoor = new ArrayList<Integer>();
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(board[i][j].getBackground() == Color.white){
                    emptycoor.add(i);
                    emptycoor.add(j);
                }
            }
        }
        return emptycoor;
    }
    @Override
    public boolean move(int x, int y, int horizontal, int vertical){
        boolean success = false;
        int xMiddle = x + vertical;
        int xLast = x + (2 * vertical);
        int yMiddle = y + horizontal;
        int yLast = y + (2 * horizontal);
        if(-1 < yLast && yLast < size && -1 < xLast && xLast < size){
            if(board[xMiddle][yMiddle].getBackground() == Color.green || board[xMiddle][yMiddle].getBackground() == Color.yellow){
                if(board[xLast][yLast].getBackground() == Color.green || board[xLast][yLast].getBackground() == Color.yellow){
                    success = true;
                    previousBoard = ButtontoString();
                    board[x][y].setBackground(Color.green);
                    board[xMiddle][yMiddle].setBackground(Color.white);
                    board[xLast][yLast].setBackground(Color.white);
                }
            }
        }
        return success;
    }
    @Override
    public boolean autoPlay(){
        ArrayList<Integer> emptycoor = emptyCoor();
        Random random = new Random();
        boolean success = false;
        int index, direction;
        for(int j = 0; j < emptycoor.size()/2 && success == false; j++){
            int[] directionArray = {1, 2, 3, 4};
            for(int i = 0; i < 4 && success == false; i++){
                do{
                    index = random.nextInt(4);
                    direction = directionArray[index];
                }while(direction == -1);
                directionArray[index] = -1;
                switch(direction){
                    case 1:
                        success = move(emptycoor.get(2*j), emptycoor.get(2*j+1), 0, 1);
                        break;
                    case 2:
                        success = move(emptycoor.get(2*j), emptycoor.get(2*j+1), 0, -1);
                        break;
                    case 3:
                        success = move(emptycoor.get(2*j), emptycoor.get(2*j+1), 1, 0);
                        break;
                    case 4:
                        success = move(emptycoor.get(2*j), emptycoor.get(2*j+1), -1, 0);
                        break;
                }
            }
        }
        updateScore();
        return success;
    }
    @Override
    public boolean userPlay(int pegCellX, int pegCellY, int emptyCellX, int emptyCellY){
        int xDifference = pegCellX - emptyCellX;
        int yDifference = pegCellY - emptyCellY;
        boolean success = false;
        if(((xDifference == 2 || xDifference == -2) && yDifference == 0) || (yDifference == 2 || yDifference == -2) && xDifference == 0){ 
            int middleCellX = (pegCellX + emptyCellX)/2;
            int middleCellY = (pegCellY + emptyCellY)/2;
            if(board[pegCellX][pegCellY].getBackground() == Color.yellow){
                if(board[middleCellX][middleCellY].getBackground() == Color.green){
                    if(board[emptyCellX][emptyCellY].getBackground() == Color.white){
                        previousBoard = ButtontoString();
                        board[emptyCellX][emptyCellY].setBackground(Color.green);
                        board[middleCellX][middleCellY].setBackground(Color.white);
                        board[pegCellX][pegCellY].setBackground(Color.white);
                        success = true;
                        updateScore();
                    }
                }
            }
        }
        return success;
    }
    @Override
    public void updateScore(){
        calculateScore();
        scoreText.setVisible(false);
        settings.remove(scoreText);
        scoreText.setText("Score: " + score);
        scoreText.setVisible(true);
        settings.add(scoreText);
        settings.repaint();
    }
    @Override
    public void calculateScore(){
        score = -1;
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(board[i][j].getBackground() == Color.green || board[i][j].getBackground() == Color.yellow){
                    score++;
                }
            }
        }
    }
    @Override
    public void changeType(){
        switch(currentType){
            case 1:
                StringtoButton(first_type());
                break;
            case 2:
                StringtoButton(second_type());
                break;
            case 3:
                StringtoButton(third_type());
                break;
            case 4:
                StringtoButton(fourth_type());
                break;
            case 5:
                StringtoButton(fifth_type());
                break;
        }
    }
    @Override
    public final void StringtoButton(String[][] virtualBoard){
        size = virtualBoard.length;
        board = new JButton[size][size];
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                board[i][j] = new JButton();
                switch(virtualBoard[i][j]){
                    case "wall":
                        board[i][j].setBackground(Color.gray);
                        break;
                    case "peg":
                        board[i][j].setBackground(Color.green);
                        break;
                    case "empty":
                        board[i][j].setBackground(Color.white);
                        break;
                }
            }
        }
    }
    @Override
    public String[][] ButtontoString(){
        String[][] virtualBoard = new String[size][size];
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                virtualBoard[i][j] = new String();
                if(board[i][j].getBackground() == Color.green || board[i][j].getBackground() == Color.yellow){
                    virtualBoard[i][j] = "peg";
                }
                else if(board[i][j].getBackground() == Color.gray){
                    virtualBoard[i][j] = "wall";
                }
                else if(board[i][j].getBackground() == Color.white){
                    virtualBoard[i][j] = "empty";
                }
            }
        }
        return virtualBoard;
    }
    @Override
    public final String[][] first_type(){
        currentType = 1;
        String[][] virtualBoard = {
            {"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
            {"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
            {"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
            {"peg", "peg", "peg", "peg", "peg", "peg", "peg", "peg", "peg"},
            {"peg", "peg", "peg", "peg", "empty", "peg", "peg", "peg", "peg"},
            {"peg", "peg", "peg", "peg", "peg", "peg", "peg", "peg", "peg"},
            {"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
            {"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
            {"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"}
	};
        initialBoard = virtualBoard;
        return virtualBoard;
    }
    @Override
    public final String[][] second_type(){
        currentType = 2;
        String[][] virtualBoard ={
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall"},
		{"wall", "peg", "peg", "peg", "peg", "peg", "wall"},
		{"peg", "peg", "peg", "empty", "peg", "peg", "peg"},
		{"peg", "peg", "peg", "peg", "peg", "peg", "peg"},
		{"peg", "peg", "peg", "peg", "peg", "peg", "peg"},
		{"wall", "peg", "peg", "peg", "peg", "peg", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall"}
	};
        initialBoard = virtualBoard;
        return virtualBoard;
    }
    @Override
    public final String[][] third_type(){
        currentType = 3;
        String[][] virtualBoard = {
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
		{"peg", "peg", "peg", "peg", "peg", "peg", "peg", "peg"},
		{"peg", "peg", "peg", "empty", "peg", "peg", "peg", "peg"},
		{"peg", "peg", "peg", "peg", "peg", "peg", "peg", "peg"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"}
	};      
        initialBoard = virtualBoard;
        return virtualBoard;
    }
    @Override
    public final String[][] fourth_type(){
        currentType = 4;
        String[][] virtualBoard = {
                {"wall", "wall", "peg", "peg", "peg", "wall", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall"},
		{"peg", "peg", "peg", "peg", "peg", "peg", "peg"},
		{"peg", "peg", "peg", "empty", "peg", "peg", "peg"},
		{"peg", "peg", "peg", "peg", "peg", "peg", "peg"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "wall", "wall"}
        };
        initialBoard = virtualBoard;
        return virtualBoard;
    }
    @Override
    public final String[][] fifth_type(){
        currentType = 5;
        String[][] virtualBoard = {
                {"wall", "wall", "wall", "wall", "peg", "wall", "wall", "wall", "wall"},
		{"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "peg", "peg", "wall", "wall"},
		{"wall", "peg", "peg", "peg", "peg", "peg", "peg", "peg", "wall"},
		{"peg", "peg", "peg", "peg", "empty", "peg", "peg", "peg", "peg"},
		{"wall", "peg", "peg", "peg", "peg", "peg", "peg", "peg", "wall"},
		{"wall", "wall", "peg", "peg", "peg", "peg", "peg", "wall", "wall"},
		{"wall", "wall", "wall", "peg", "peg", "peg", "wall", "wall", "wall"},
		{"wall", "wall", "wall", "wall", "peg", "wall", "wall", "wall", "wall"}
        };
        initialBoard = virtualBoard;
        return virtualBoard;
    }
    /**
     * Main method for this class.
     * @param args Arguments for main.
     */
    public static void main(String[] args){
        var gui = new GUI();
    }
}
