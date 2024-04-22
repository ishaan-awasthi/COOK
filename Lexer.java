public class Lexer {
    public Lexer(){}

    public Object[] analyze(String line, String key) {
        // Lexical analysis and tokenization
        // AKA isolating the relevant tokens

        try {
            line = line.toLowerCase();

            if (key.equals("until")) {
                String condition;
                String sub = line.substring(line.indexOf("until the") + 10);
                String first = sub.substring(0, findEndDelimiter(sub, 0));
                String second = "";

                if (line.contains("is more than")) {
                    condition = "until more";
                    sub = line.substring(line.indexOf(first) + first.length() + 1);
                    sub = sub.substring(sub.indexOf("the") + 4);
                    second = sub.substring(0, findEndDelimiter(sub, 0));
                } else if (line.contains("is less than")) {
                    condition = "until less";
                    sub = line.substring(line.indexOf(first) + first.length() + 1);
                    sub = sub.substring(sub.indexOf("the") + 4);
                    second = sub.substring(0, findEndDelimiter(sub, 0));
                } else if (line.contains("is equal to")) {
                    condition = "until equal";
                    sub = line.substring(line.indexOf(first) + first.length() + 1);
                    sub = sub.substring(sub.indexOf("the") + 4);
                    second = sub.substring(0, findEndDelimiter(sub, 0));
                } else if (line.contains("is gone")) {
                    condition = "until gone";
                } else {
                    condition = null;
                }
                return new Object[]{condition, first, second};
            }

            if (key.equals("conditional")) {
                String condition;
                String sub = line.substring(line.indexOf("the") + 4);
                String first = sub.substring(0, findEndDelimiter(sub, 0));
                String second = "";

                if (line.contains("is more than")) {
                    condition = "is more";
                    sub = line.substring(line.indexOf(first) + first.length() + 1);
                    sub = sub.substring(sub.indexOf("the") + 4);
                    second = sub.substring(0, findEndDelimiter(sub, 0));
                } else if (line.contains("is less than")) {
                    condition = "is less";
                    sub = line.substring(line.indexOf(first) + first.length() + 1);
                    sub = sub.substring(sub.indexOf("the") + 4);
                    second = sub.substring(0, findEndDelimiter(sub, 0));
                } else if (line.contains("is equal to")) {
                    condition = "is equal";
                    sub = line.substring(line.indexOf(first) + first.length() + 1);
                    sub = sub.substring(sub.indexOf("the") + 4);
                    second = sub.substring(0, findEndDelimiter(sub, 0));
                } else if (line.contains("is gone")) {
                    condition = "is gone";
                } else if (line.contains("is same brand as")) {
                    condition = "string equals";
                    sub = line.substring(line.indexOf(first) + first.length() + 1);
                    sub = sub.substring(sub.indexOf("the") + 4);
                    second = sub.substring(0, findEndDelimiter(sub, 0));
                } else {
                    condition = null;
                }
                return new Object[]{condition, first, second};
            }

            if (key.equals("input")) {
                String sub = line.contains("find how much of the")
                        ? line.substring(line.indexOf("find how much of the") + 21)
                        : line.substring(line.indexOf("find what brand of the") + 23);
                String value = sub.substring(0, findEndDelimiter(sub, 0));
                return new Object[]{value};
            }

            if (key.equals("print")) {
                String sub = line.substring(line.indexOf("the") + 4);
                String value = sub.substring(0, findEndDelimiter(sub, 0));
                return new Object[]{value};
            }

            if (key.equals("int")) {
                // Regex is used to isolate the ints in the line

                String sub = line.substring(line.indexOf("of") + 3);
                String varname = sub.substring(0, findEndDelimiter(sub, 0));
                Integer value = line.matches(".*\\d.*")
                        ? Integer.parseInt(line.replaceAll("\\D", ""))
                        : 0;
                return new Object[]{varname, value};
            }

            if (key.equals("String")) {
                String sub = line.substring(line.indexOf("brand") + 6);
                String varname = sub.substring(0, findEndDelimiter(sub, 0));
                String value = line.substring(line.indexOf("\"") + 1, line.lastIndexOf("\""));

                return new Object[]{varname, value};
            }

            if (key.equals("add") || key.equals("subtract")) {
                // Same syntax is used for addition/subtraction, excluding the key

                String sub = line.substring(line.indexOf("in the") + 7);
                String populate = sub.substring(0, findEndDelimiter(sub, 0));
                sub = line.substring(line.indexOf(populate) + populate.length() + 1);
                sub = sub.substring(sub.indexOf("the") + 4);
                String first = sub.substring(0, findEndDelimiter(sub, 0));
                sub = line.substring(line.indexOf(populate) + populate.length() + 1);
                sub = sub.substring(sub.indexOf(first) + first.length() + 1);
                sub = sub.substring(sub.indexOf("the") + 4);
                String second = sub.substring(0, findEndDelimiter(sub, 0));
                return new Object[]{populate, first, second};
            }

            if (key.equals("multiply") || key.equals("divide")) {
                // Same syntax is used for multiplication/division, excluding the key

                String sub = line.substring(line.indexOf("in the") + 7);
                String populate = sub.substring(0, findEndDelimiter(sub, 0));
                sub = line.substring(line.indexOf(sub));
                sub = sub.substring(sub.indexOf("the") + 4);
                String first = sub.substring(0, findEndDelimiter(sub, 0));
                sub = line.substring(line.indexOf("into the") + 9);
                String second = sub.substring(0, findEndDelimiter(sub, 0));
                return new Object[]{populate, first, second};
            }

            if (key.equals("mod")) {
                String sub = line.substring(line.indexOf("in the") + 7);
                String populate = sub.substring(0, findEndDelimiter(sub, 0));
                sub = line.substring(line.indexOf(sub));
                sub = sub.substring(sub.indexOf("excess") + 7);
                String first = sub.substring(0, findEndDelimiter(sub, 0));
                sub = line.substring(line.indexOf("into the") + 9);
                String second = sub.substring(0, findEndDelimiter(sub, 0));
                return new Object[]{populate, first, second};
            }

            return new Object[]{};
        } catch (IndexOutOfBoundsException e) {
            throw new Error("\n\nError: Double-check your syntax (especially article pointers)!\n" + e.getMessage());
        } catch (NumberFormatException e) {
            throw new Error("\n\nError: Did you mean to use that String?\n" + e.getMessage());
        } catch (NullPointerException e) {
            throw new Error("\n\nDouble-check your syntax (especially article pointers)!\n" + e.getMessage());
        } catch (Exception e) {
            throw new Error("\n\nError: Unknown exception occurred during tokenization.\n" + e.getMessage());
        }
    }

    private int findEndDelimiter(String sub, int startIndex) {
        // Helper method that identifies where tokens end

        int spaceIndex = sub.indexOf(' ', startIndex);
        int periodIndex = sub.indexOf('.', startIndex);
        int commaIndex = sub.indexOf(',', startIndex);
        int exclamationIndex = sub.indexOf('!', startIndex);
        int questionIndex = sub.indexOf('?', startIndex);

        int smallestIndex = sub.length();
        if (spaceIndex != -1 && spaceIndex < smallestIndex) smallestIndex = spaceIndex;
        if (periodIndex != -1 && periodIndex < smallestIndex) smallestIndex = periodIndex;
        if (commaIndex != -1 && commaIndex < smallestIndex) smallestIndex = commaIndex;
        if (exclamationIndex != -1 && exclamationIndex < smallestIndex) smallestIndex = exclamationIndex;
        if (questionIndex != -1 && questionIndex < smallestIndex) smallestIndex = questionIndex;

        return smallestIndex;
    }
}
