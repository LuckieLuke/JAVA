package durnoga;

public class Test2 {

    static void test(IStack s) {

        s.push(3);
        s.push(47);
        s.push("alpaca");

        System.out.println(s);


        System.out.println(s.pop());
        System.out.println(s.top());
        System.out.println(s.isEmpty());
        System.out.println(s);
        System.out.println(s.pop());
        System.out.println(s.isEmpty());
        System.out.println(s);
        System.out.println(s.pop());
        System.out.println(s);
        System.out.println(s.pop());
    }

    public static void test2() {
        test(new Stack());
        System.out.println("------------");
        test(new ArrayStack());
        System.out.println("------------");
        test(new YetAnotherStack());
    }

    public static void main(String[] args) {
        test2();


    }

}
