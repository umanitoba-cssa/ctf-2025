import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

class Solution {
    public static void main(String[] args) {
        try {
            File myObj = new File("detective_gpt.txt");
            Scanner myReader = new Scanner(myObj);
            FileWriter writer = new FileWriter("solution.txt");
            while (myReader.hasNextLine()) {
                String msg = myReader.nextLine();
                // first n-1 are actual message bits encoded in ascii
                int p = countOnesParity(msg.substring(0, msg.length() - 1));
                // get the parity value which is the last digit
                int pair = Character.getNumericValue(msg.charAt(msg.length() - 1));
                // if they parity bit and the number of ones odd/even don't match. we know its added in
                if (p != pair) {
                    writer.write(msg.substring(0, msg.length() - 1) + "\n");
                }
            }
            myReader.close();
            writer.close();
        } catch (FileNotFoundException e) {

        } catch (IOException e) {

        }
    }


    public static int countOnesParity(String c) {
        int count = 0;
        for (int i = 0; i < c.length(); i++) {
            if (c.charAt(i) == '1') {
                count++;
            }
        }
        return count % 2;
    }
}