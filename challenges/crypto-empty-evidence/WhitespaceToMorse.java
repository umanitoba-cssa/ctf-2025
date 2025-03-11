import java.io.File;  // Import the File class
import java.io.FileNotFoundException;  // Import this class to handle errors
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner; // Import the Scanner class to read text files

class WhitespaceToMorse {
    public static void main(String[] args) {
        // read whitespace into morse code
        try {
            File myObj = new File("output.txt");
            Scanner myReader = new Scanner(myObj);
            FileWriter writer = new FileWriter("decoded.txt");
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                String toWrite = "-1";
                for (int i = 0; i < data.length(); i++) {
                            switch (data.charAt(i)) {
                                case '\t':
                                    toWrite = ".";
                                    break;
                                case ' ':
                                    toWrite = " ";
                                    break;
                                default:
                                    System.out.println("uh oh");
                                    break;
                            }      
                    writer.write(toWrite);
                }
                // new line is always a - and we can predict when it happens with \n
                writer.write("-");
            }
            writer.close();
            myReader.close();
        } catch (FileNotFoundException e) {

        } catch (IOException e) {
        }
    }
}
