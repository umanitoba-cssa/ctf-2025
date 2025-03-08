class RePrimeSuspect {
    public static int[][] arr = new int[12][30];
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Enter your key");
            System.exit(1);
        }
        if (args[0].length() != 10) {
            System.out.println("Enter ONLY 10 characters");
            System.exit(1);
        }
        String str = "CSSAHostingCTF";
        for (int i = 0; i < 10; i++) {
            decompInt(str.charAt(i), i);
        }
        if(args[0].equals(toString(arr))) {
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
                        arr[row][prime_N(130,num)] = 1;
                    }
                    else if (counter > 1) {
                        arr[row][prime_N(130,num)] = counter;
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
        for (int sec = 0; sec < 10; sec++) {
            int sum = 0;
            for (int row = 0; row < 10; row++) {
                for (int col = 0; col < 3; col++) {
                    sum += a[row][3*sec + col];
                }
            }
            int corrected = sum + 'A';
            toReturn += (char)corrected;
        }
        // 10 characters long
        System.out.println(toReturn);
        return toReturn;
    }
}