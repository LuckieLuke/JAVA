package durnoga;

import org.junit.*;

import static org.junit.Assert.*;

public class Test2Test {

    private ArrayStack s;

    @BeforeClass
    public static void beforeAll() {
        System.out.println("Przed wszystkim");
    }

    @Before
    public void before() {
        System.out.println("Przed każdym testem");
        s = new ArrayStack();
    }

    @After
    public void after() {
        System.out.println("Po każdym teście");
    }

    @AfterClass
    public static void afterAll() {
        System.out.println("Po wszystkim");
    }

    @Test
    public void testEmptyStack() {
        assertTrue("stos nie jest pusty", s.isEmpty()); //assertTrue to statyczna metoda
    }

    @Test
    public void testPushAndPop() {
        s.push(42);
        assertEquals("Powinno być 42, debilu", 42, s.pop());
        assertTrue("znowu nie jest pusty", s.isEmpty());
    }

    //@Test
    public void f() {
        //bez @Test JUnit nie traktuje metody jako testu
    }

    @Test
    public void testTop() {
        s.push(34);
        assertEquals("Spierdalaj", 34, s.top());
    }

}