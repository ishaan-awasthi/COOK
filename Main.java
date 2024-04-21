import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(new File(new File(".").getAbsolutePath()+"/src/sample.txt"));
            Classifier classifier = new Classifier();
            Lexer lexer = new Lexer();
            Interpreter interpreter = new Interpreter();
            HashMap<String, Object> variables = new HashMap();

            while (scanner.hasNextLine()) {
                String current = scanner.nextLine();
                String keyword = classifier.classify(current);
                Object[] tokens = lexer.analyze(current, keyword);
                interpreter.execute(keyword, tokens, variables);
            }

        } catch (FileNotFoundException e) {
            System.out.println("ERROR NO FILE: " + e.getMessage());
        }
    }
}