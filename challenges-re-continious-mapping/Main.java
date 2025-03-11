

public class Main {
	private static char[] dict = new char[26];

    public static void build() {
        Da da = new Da();
        Db db = new Db();
        Dc dc = new Dc();
        Dd dd = new Dd();
        De de = new De();
        Df df = new Df();

        dd.tr(dict);
        df.tr(dict);
        de.tr(dict);
        db.tr(dict);
        da.tr(dict);
        dc.tr(dict);
    }

    public static void main(String[] args) {
        build();
        String key = args[0];

        if (key.length() != 10) {
            System.out.println("false");
            return;
        }

        String transformed = "";
        String Target = "CGUPPMMCMI";
        for (int i = 0; i < key.length(); i++) {
            if (key.charAt(i) == Target.charAt(i)) {
                System.out.println("false");
                //return;
            }
            int o = key.length() % (i+1);
            transformed += map(key.charAt(i), o);
            System.out.println(o);
        }
        System.out.println(transformed);
        if (transformed.equals(Target)) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }

    }
	
	public static char map(char c, int r) {
        char x = dict[c - 'A'];
        if (r > 0) {
            return map(x, r - 1);
        } else {
            return x;
        }
	}
}