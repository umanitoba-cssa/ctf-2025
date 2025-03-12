import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
class ReadFile {
    
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Enter only one word");
            return;
        }
        if (args[0].length() != 15) {
            System.out.println("15 characters only");
            return;
        }
        char[] arr = new char[26];
        boolean done = false;
        int count = 0;
        String target = "YDARUGDCDDSVPTD";
        try {
            File myObj = new File("script.txt");
            Scanner myReader = new Scanner(myObj);
            while(myReader.hasNextLine() && !done) {
                String s = myReader.nextLine();
                if (s.contains(":")) {
                    String[] sArr = s.split(":");
                    if(sArr.length != 2) {
                        continue;
                    }
                    String s1 = sArr[1];
                    for (int i = 0; i < s1.length(); i++) {
                        char c = s1.charAt(i);
                        if (!Character.isLetter(c)) {
                            continue;
                        }
                        c = Character.toUpperCase(c);
                        if(!has(arr,c,count)) {
                            if (count < 26) {
                                arr[count] = c;
                                count++;
                            } else {
                                done = true;
                            }
                        }
                    }
                }

            }
        } catch (FileNotFoundException e) {

        }
        String output = "";
        for (int i = 0; i < args[0].length(); i++) {
            output += arr[args[0].charAt(i) - 'A'];
        }
        System.out.println(output);
        if (output.equals(target)) {
            System.out.println("Success");
        } else {
            System.out.println("Nope");
        }
        System.out.println("hello world");
        for (char c : arr) {
            System.out.print(c + ",");
        }
    }
    
    public static boolean has(char[] a, char target, int size) {
        boolean toReturn = false;
        for(int i = 0; i < Math.min(size, 26); i++) {
            if(target == a[i]) {
                toReturn = true;
                break;
            }
        }   
        return toReturn;
    }
}