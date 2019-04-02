package durnoga;

public class Stack implements IStack{

    private StackElem top;

    public Stack() {
        this.top = null;
    }

    public void push(Object value) {
        top = new StackElem(value, top);
    }

    public Object pop() {
        if (isEmpty()) {
            System.err.println("Zdjecie z pustego stosu");
            return null;
        }

        Object result = top.getValue();
        top = top.getNext();
        return result;
    }

    public boolean isEmpty() {
        return top == null;
    }

    public Object top() {
        return top.getValue();
    }

    public String toString() {
        if(isEmpty()) {
            return "[]";
        }

        StringBuilder builder = new StringBuilder();

        StackElem tmp = top;
        while(tmp != null) {
            builder.insert(0, tmp.getValue() + ", ");
            tmp = tmp.getNext();
        }
        if(builder.length() >= 2)
            builder.delete(builder.length() - 2, builder.length());


        return "[" + builder.toString() + "]";
    }


}
