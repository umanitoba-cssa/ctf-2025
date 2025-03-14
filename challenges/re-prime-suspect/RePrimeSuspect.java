class RePrimeSuspect {
    public static int[][] arr = new int[12][16];
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Enter your key");
            System.exit(1);
        }
        if (args[0].length() < 12) {
            System.out.println("Enter ONLY 12 characters or less");
            System.exit(1);
        }
        if (args[0].contains("B")) 
        {
            System.out.println("Enter no A's");
            System.exit(1);     
        }
        if(!isInOrder(args[0])) {
            System.out.println("Order your word");
            System.exit(1);    
        }
        if(!check(args[0])) {
            System.out.println("Misplaced character");
            System.exit(1);    
        }
        String target = "IFBAABCCAAAAAABA";
        String str = args[0];
        for (int i = 0; i < str.length(); i++) {
            decompInt(str.charAt(i) - 'A' + 1, i);
        }
        if(target.equals(toString(arr))) {
            System.out.println("Secret Message");
        } else {
            System.out.println("Nope Try Again");
        }
    }

    static void decompInt(int n, int row) {
        int num = 2;
        while (num <= n) {
            int i = 2;
            boolean isPrime = true;
            while (i < num && isPrime) {
                if (num % i == 0) {
                    isPrime = false;
                }
                i++;
                }
                if (isPrime) {
                    int counter = 0;
                    while (n >= num && n % num == 0) {
                        counter++;
                        n /= num;
                    }

                    if (counter == 1) {
                        arr[row][prime_N(58,num)] = 1;
                    }
                    else if (counter > 1) {
                        arr[row][prime_N(58,num)] = counter;
                    }
                }
                num++;
        }
    }

    // N how long the loop is to prevent infinite loop. 130 is the max it'll reach
    // Please don't judge me 
    static int prime_N(int N, int target)
    {
        // Declaring the variables
        int x, y, flg;
        int index = 0;

        for (x = 1; x <= N; x++) {

            if (x == 1 || x == 0)
                continue;

            flg = 1;

            for (y = 2; y <= x / 2; ++y) {
                if (x % y == 0) {
                    flg = 0;
                    break;
                }
            }

            if (flg == 1) {
                if (x == target) {
                    return index;
                } else {
                    index++;
                }
            }
                //System.out.print(x + " ");
        }
        return -1;
    }

    static String toString(int[][] a) {
        String toReturn = "";
            for (int col = 0; col < 16; col++) {
                int sum = 0;
                for (int row = 0; row < 12; row++) {
                    sum += a[row][col];
                }
                int corrected = sum + 'A';
                toReturn += (char)corrected;
            }
        return toReturn;
    }

    static boolean isInOrder(String str) {
        char[] arr = str.toCharArray();
        char previous = '\u0000';
        for (char current : arr) {
            if (current < previous)
                return false;
            previous = current;
        }
        return true;
    }
    static boolean check(String str) {
        boolean check1 = str.charAt(2) == str.charAt(3);
        boolean check2 = str.charAt(5) == str.charAt(6);
        boolean check3 = str.charAt(7) == str.charAt(8);
        boolean check4 = str.charAt(9) == str.charAt(10);
        int sum = 0;
        for (char c : str.toCharArray()) {
            sum += c;
        }
        boolean check5 = (sum == 958);
        return check1 && check2 && check3 && check4 && check5;
    }
}
