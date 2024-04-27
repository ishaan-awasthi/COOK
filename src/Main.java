import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            // Helper classes for compilation
            Scanner scanner = new Scanner(new File(new File("").getAbsolutePath()+"/src/sample.txt"));
            Classifier classifier = new Classifier();
            Lexer lexer = new Lexer();
            Interpreter interpreter = new Interpreter();
            HashMap<String, Object> variables = new HashMap<>();

            // Runtime loop
            while (scanner.hasNextLine()) {
                String current = scanner.nextLine();
                String key = classifier.classify(current);
                Object[] tokens = lexer.analyze(current, key);
                interpreter.execute(key, tokens, variables, scanner, classifier, lexer, interpreter);
            }

        } catch (FileNotFoundException e) {
            throw new Error("\n\nError: File not found!\n" + e.getMessage());
        }
    }
}
