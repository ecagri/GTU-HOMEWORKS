package cayci;
import java.util.ArrayList;
import javax.swing.*;
/**
 * 
 * @author Cagri Cayci
 */
public interface PegSolitaireGame {
        /**
     * Creates a JPanel to show the board, adds ActionListener which user can make moves to the all buttons on the board.
     * @return Returns a JPanel.
    */
    public abstract JPanel tablePanel();
    /**
     * Creates a JButton with an ActionListener which returns the previous state of the board.
     * @return Returns a JButton named UNDO.
    */
    public abstract JButton undoButton();
    /**
     * Creates a JButton with an ActionListener which returns the initial state of the board.
     * @return Returns a JButton named RESET.
    */
    public abstract JButton resetButton();
    /**
     * Creates a JButton with an ActionListener which saves the current state of the board as a .txt file.
     * @return Returns a JButton named SAVE.
    */
    public abstract JButton saveButton();
    /**
     * Creates a JButton with an ActionListener which loads a board from a .txt file.
     * @return Returns a JButton named LOAD.
    */
    public abstract JButton loadButton();
    /**
     * Creates a JRadioButton array with ActionListeners which changes the type of the board. 
     * @return Returns a JRadioButton array.
    */
    public abstract JRadioButton[] typeButtons();
    /**
     * Creates a JButton with an ActionListener which plays one move automatically. 
     * @return Returns a JButton named PLAY AUTO.
    */
    public abstract JButton playAutoButton();
    /**
     * Creates a JButton with an ActionListener which plays all move automatically.
     * @return Returns a JButton named PLAY AUTO ALL.
    */
    public abstract JButton playAutoAllButton();
    /**
     * Creates a JPanel with all settings buttons.
     * @return Returns a JPanel.
    */
    public abstract JPanel settingsPanel();
    /**
     * Changes the type of the board.
    */
    public abstract void changeType();
    /**
     * Convert 2D String array into 2D JButton array.
     * @param virtualBoard 2D String array which represents a board.
    */
    public abstract void StringtoButton(String[][] virtualBoard);
    /**
     * Convert 2D JButton array of current board into 2D String array.
     * @return Returns the current state of board as 2D String array.
    */
    public abstract String[][] ButtontoString();
    /**
     * Finds empty cells on the board and adds coordinates of empty cells to an ArrayList.
     * @return Returns an ArrayList.
    */
    public abstract ArrayList<Integer> emptyCoor();
    /**
     * Checks the given coordinates, and move the cells if it can.
     * @param x int for x coordinate of empty cell.
     * @param y int for y coordinate of empty cell.
     * @param horizontal int for horizontal direction.
     * @param vertical int for Vertical direction.
     * @return Returns true if it can move, otherwise false.
    */
    public abstract boolean move(int x, int y, int horizontal, int vertical);
    /**
     * Finds empty coordinates, try all empty coordinates until the cell move in any direction. 
     * @return Returns true if it can move, otherwise false.
    */
    public abstract boolean autoPlay();
    /**
     * Evaluate given coordinates whether it meets the conditions, if it meets makes a move.
     * @param pegCellX int for x coordinate for peg.
     * @param pegCellY int for y coordinate for peg.
     * @param emptyCellX int for x coordinate for empty.
     * @param emptyCellY int for y coordinate for empty.
     * @return Returns true if it meets the conditions, otherwise false.
    */
    public abstract boolean userPlay(int pegCellX, int pegCellY, int emptyCellX, int emptyCellY);
    /**
     * Updates the sccore.
    */
    public abstract void updateScore();
    /**
     * Calculates the score.
    */
    public abstract void calculateScore();
    /**
     * First type for board.
     * @return Returns a 2D String array which represents a board.
    */
    public abstract String[][] first_type();
    /**
     * Second type for board.
     * @return Returns a 2D String array which represents a board.
    */
    public abstract String[][] second_type();
    /**
     * Third type for board.
     * @return Returns a 2D String array which represents a board.
    */
    public abstract String[][] third_type();
    /**
     * Fourth type for board.
     * @return Returns a 2D String array which represents a board.
    */
    public abstract String[][] fourth_type();
    /**
     * Fifth type for board.
     * @return Returns a 2D String array which represents a board.
    */
    public abstract String[][] fifth_type();
}
