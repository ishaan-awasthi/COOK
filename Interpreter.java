import java.util.HashMap;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Interpreter {
    public Interpreter(){}

    public void execute(String key, Object[] tokens, HashMap variables, Scanner scanner, Classifier classifier, Lexer lexer, Interpreter interpreter){
        // Code generation, converting to Java

        try{
            Scanner userinput = new Scanner(System.in);

            if(key.equals("until")){
                boolean condition = true;
                int second = !(tokens[0].equals("until gone"))
                        ? (boolean) tokens[3] ? Integer.parseInt((String) tokens[2]) : (int) variables.get(tokens[2])
                        :0;
                if(tokens[0].equals("until more")){
                    condition = (int)variables.get(tokens[1]) > second;
                } else if(tokens[0].equals("until less")){
                    condition = (int)variables.get(tokens[1]) < second;
                } else if(tokens[0].equals("until equal")){
                    condition = (int)variables.get(tokens[1]) == second;
                } else if(tokens[0].equals("until gone")){
                    condition = (int)variables.get(tokens[1]) > 0;
                } else{
                    throw new Error("\n\nError: Not a valid comparison!");
                }

                String nextline = scanner.nextLine();
                while(!condition){
                    // Recursive reference to repeated code line
                    String metakey = classifier.classify(nextline);
                    Object[] metatokens = lexer.analyze(nextline, metakey);
                    interpreter.execute(metakey, metatokens, variables, scanner, classifier, lexer, interpreter);

                    // Repeat conditionals to check if condition has been met
                    if(tokens[0].equals("until more")){
                        condition = (int)variables.get(tokens[1]) > second;
                    } else if(tokens[0].equals("until less")){
                        condition = (int)variables.get(tokens[1]) < second;
                    } else if(tokens[0].equals("until equal")){
                        condition = (int)variables.get(tokens[1]) == second;
                    } else if(tokens[0].equals("until gone")){
                        condition = (int)variables.get(tokens[1]) > 0;
                    } else{
                        throw new Error("\n\nError: Not a valid comparison!");
                    }
                }
            }

            if(key.equals("conditional")){
                boolean condition = false;
                int second = (boolean)tokens[3] ? Integer.parseInt((String) tokens[2]) : (int)variables.get(tokens[2]);;

                if(tokens[0].equals("is more")){
                    condition = (int)variables.get(tokens[1]) > second;
                } else if(tokens[0].equals("is less")){
                    condition = (int)variables.get(tokens[1]) < second;
                } else if(tokens[0].equals("is equal")){
                    condition = (int)variables.get(tokens[1]) == second;
                } else if(tokens[0].equals("is gone")){
                    condition = (int)variables.get(tokens[1]) > 0;
                } else{
                    throw new Error("\n\nError: Not a valid comparison!");
                }

                // Recursive reference to conditioned code line
                String nextline = scanner.nextLine();
                if(condition){
                    String metakey = classifier.classify(nextline);
                    Object[] metatokens = lexer.analyze(nextline, metakey);
                    interpreter.execute(metakey, metatokens, variables, scanner, classifier, lexer, interpreter);
                }
            }

            if(key.equals("input")){
                // Runtime user input is processed
                if(variables.containsKey(tokens[0]) && variables.get(tokens[0]) instanceof Integer){
                    System.out.println("Input " + tokens[0] + " amount.");
                    variables.put(tokens[0], userinput.nextInt());
                } else if(variables.containsKey(tokens[0]) && variables.get(tokens[0]) instanceof String){
                    System.out.println("Input " + tokens[0] + " brand.");
                    variables.put(tokens[0], userinput.nextLine());
                } else{
                    throw new Error("\n\nError: Either the variable \"" + tokens[0] + "\" hasn't been initialized, or you inputted the wrong data type.\n");
                }
            }

            if(key.equals("print")){
                // Can print both variables and "plain strings"
                String toprint = variables.containsKey(tokens[0])
                        ? String.valueOf(variables.get(tokens[0]))
                        : String.valueOf(tokens[0]);
                System.out.println(toprint);
            }

            if(key.equals("int")){
                variables.put(tokens[0], tokens[1]);
            }

            if(key.equals("String")){
                variables.put(tokens[0], tokens[1]);
            }

            if(key.equals("add")){
                int first = (int)variables.get(tokens[1]);
                int second = (boolean)tokens[3] ? Integer.parseInt((String) tokens[2]) : (int)variables.get(tokens[2]);;
                variables.put(tokens[0], first+second);
            }

            if(key.equals("subtract")){
                int first = (int)variables.get(tokens[1]);
                int second = (boolean)tokens[3] ? Integer.parseInt((String) tokens[2]) : (int)variables.get(tokens[2]);;
                variables.put(tokens[0], first-second);
            }

            if(key.equals("multiply")){
                int first = (int)variables.get(tokens[1]);
                int second = (boolean)tokens[3] ? Integer.parseInt((String) tokens[2]) : (int)variables.get(tokens[2]);;
                variables.put(tokens[0], first*second);
            }

            if(key.equals("divide")){
                int first = (int)variables.get(tokens[1]);
                int second = (boolean)tokens[3] ? Integer.parseInt((String) tokens[2]) : (int)variables.get(tokens[2]);;
                variables.put(tokens[0], first/second);
            }

            if(key.equals("mod")){
                int first = (int)variables.get(tokens[1]);
                int second = (boolean)tokens[3] ? Integer.parseInt((String) tokens[2]) : (int)variables.get(tokens[2]);;
                variables.put(tokens[0], first%second);
            }
        } catch (IndexOutOfBoundsException e) {
            throw new Error("\n\nError: Double-check your syntax (especially article pointers)!\n" + e.getMessage());
        } catch (NumberFormatException e) {
            throw new Error("\n\nError: Did you mean to use that String?\n" + e.getMessage());
        } catch (NullPointerException e) {
            throw new Error("\n\nDouble-check your syntax (especially article pointers)!\n" + e.getMessage());
        } catch (NoSuchElementException e) {
            throw new Error("\n\nError: Input mismatch or unexpected end of input!\n" + e.getMessage());
        } catch (ArithmeticException e) {
            throw new Error("\n\nError: Arithmetic exception occurred during calculation!\n" + e.getMessage());
        } catch (Exception e) {
            throw new Error("\n\nError: Unknown exception occurred during execution.\n" + e.getMessage());
        }
    }
}
