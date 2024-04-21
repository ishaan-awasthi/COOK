import java.util.HashMap;

public class Interpreter {
    public Interpreter(){}

    public void execute(String keyword, Object[] tokens, HashMap variables){
        if(keyword.equals("print")){
            String toprint = variables.containsKey(tokens[0])
                    ? String.valueOf(variables.get(tokens[0]))
                    : String.valueOf(tokens[0]);
            System.out.println(toprint); //LEAVE THIS
        }

        if(keyword.equals("int")){
            variables.put(tokens[0], tokens[1]);
        }

        if(keyword.equals("String")){
            variables.put(tokens[0], tokens[1]);
        }

        if(keyword.equals("add")){
            int first = (int)variables.get(tokens[1]);
            int second = (int)variables.get(tokens[2]);
            variables.put(tokens[0], first+second);
        }

        if(keyword.equals("subtract")){
            int first = (int)variables.get(tokens[1]);
            int second = (int)variables.get(tokens[2]);
            variables.put(tokens[0], first-second);
        }

        if(keyword.equals("multiply")){
            int first = (int)variables.get(tokens[1]);
            int second = (int)variables.get(tokens[2]);
            variables.put(tokens[0], first*second);
        }

        if(keyword.equals("divide")){
            int first = (int)variables.get(tokens[1]);
            int second = (int)variables.get(tokens[2]);
            variables.put(tokens[0], first/second);
        }

        if(keyword.equals("mod")){
            int first = (int)variables.get(tokens[1]);
            int second = (int)variables.get(tokens[2]);
            variables.put(tokens[0], first%second);
        }
    }
}
