> "Why programmers like cooking: you peel the carrot, you chop the carrot, and you put the carrot in the stew.  You don’t suddenly find out that your peeler is several versions behind and they dropped support for carrots in 4.3." —Randall Koutnik

<p align="center">
  <img src="https://i.ibb.co/VSy6LPY/Screenshot-2024-04-25-at-1-25-01-PM-removebg-preview-1-6.png" alt="Screenshot-2024-04-25-at-1-25-01-PM-removebg-preview-1-6" border="0">
</p>

<p>🎉 Welcome to COOK v1.0:</p>
<p>⚡ A statically-typed & selectively-interpreted esoteric language...</p>
<p>💪 ...with a forgiving English syntax and built-in standard library!</p>
<p>⭐ Drop me a star if you find this cool, it's like caffeine for my motivation.</p>
<p> </p>




<h1>Overview</h1>

Novice coders are often told that coding is like cooking, and programs themselves are often compared to recipes. Inspired by this analogy, COOK (Compiler for Object-Oriented Keys) is an esoteric programming language that blends the art of cooking with the precision of code. Built on top of Java, the language balances pointed functionality with a plain-English syntax, making it intuitive to both beginners and **seasoned** programmers (pun intended). And, through the selective tokenization of compiler-defined keys, programs written in COOK are even crafted to resemble the recipes in a cookbook.

Grab your favorite spatula, and let's get started!




<p> </p>
<h1>Setup and I/O</h1>

Clone the repository to your Desktop, and create a new Java project in your preferred IDE. I'm partial to IntelliJ IDEA for Java, which automatically creates all the directories for the JDK. Whichever IDE you prefer, copy the Java class files from your clone to the `/src/` subdirectory in your created project.

COOK programs are written line-by-line in `.txt` files. After cloning the repository, you'll need to edit the following line in the `Main.java` class to reference your COOK program:
```
Scanner scanner = new Scanner(new File(new File("").getAbsolutePath()+"/src/sample.txt"));
```
The standard stream for both output and error handling (as well as runtime user input; see the section on COOK's <a href="https://github.com/ishaan-awasthi/COOK?tab=readme-ov-file#very-limited-standard-library">Standard Library</a>) is the process terminal of your IDE. After writing your code, you'll execute it via `Main.java` in your IDE itself.




<p> </p>
<h1>Declaration</h1>

COOK supports two variable types: integers and strings. As with all processes in COOK, you will need to signal to the compiler that you intend to declare a variable using a key: ``measure`` for integers and ``prepare`` for strings. The stripped-down syntax for both declarations is as follows:
```
Measure 5 cups of int-name
Prepare a bowl of "string-value" brand string-name
```
COOK utilizes reference keys to point to relevant tokens such as variable names and their values (this reference key is usually the article `the`) and the creation of variables is no exception. When declaring a variable name, make sure to precede it with `of`. For integers, if you choose not to initialize the variable with a value, it will default to 0 in order to avoid any null exceptions.

COOK is a forgiving language when it comes to syntax. You can have complete freedom when it comes to adding punctuation, capitalization, filler text, putting the declaration/operation keys at the end of the line, or even putting integer values in the middle of a word — just make sure all the required parameters/tokens are included and referenced in the correct order (since x-y != y-x). For example, all of the following lines of code are valid and equivalent:
```
of int-name 5 pinches measure
Thou shalt take 5, goblets of int-name. And measure it.
It's beginning to look a lot like Christmas, so pour a gl5ss of int-name!!! and deck the halls with boughs of holly (and don't forget to measure!)
```
Not really cooking-themed that time, but hopefully you get the idea. (_Psst... check out the included `sample.txt` code for an example of COOK's intended style!_)

Also note that while (almost) any syntax works, for the purposes of this documentation I'll only be including simplified/contexual versions to ensure that the required parameters for each aspect of the functionality are clear.




<p> </p>
<h1>Computation</h1>
COOK has built-in functionality for basic arithmetic You can perform on operations on two variables together, or one variable and then one integer. The keys and references for each operation differs slightly; the semi-stripped syntax is as listed below:

<h2>Addition</h2>

The key for addition is `mix`, and the reference key is `in the` for the variable you will be populating and `the` for the other two.
```
In the bowl, mix the chicken and the rice.
In the bowl, mix the var1 and the 123.
```
The first line will perform the computation `bowl = chicken + rice`. Again, note how you can either add two variables, or add one variable and then one integer. This applies to all of the operations listed in this section.

<h2>Subtraction</h2>

The key for subtraction is `reduce`, and the reference key is `in the` for the variable you will be populating and `the` for the other two.
```
In the pot, reduce the chicken-stock from the soup.
```
For subtraction/division/modulo, make sure to reference the variables in the correct orded to perform the intended computation.

<h2>Multiplication</h2>

The key for multiplication is `fold`, and the reference key is `in the` for the variable you will be populating and `the` for the other two.
```
In the plate, fold the dough into the 4 number of layers.
```
Here we are multiplying by an integer. This always needs to come second and still needs a reference!

<h2>Division</h2>

The key for divison is `divide`, and the reference key is `in the` for the variable you will be populating and `the` for the other two.
```
In the tray, divide the cheese into the people number of portions.
```

<h2>Modulo</h2>

With modulo, `excess` serves both as the operation key and the reference key for the first variable. Use `in the` for the variable to be populated and `the` for the second variable/integer.
```
In the tray, save the excess cheese after dividing into the people number of portions.
```
Note the similarity in syntax to divison.




<p> </p>
<h1>Conditionals</h1>

Intuitively, the `if` keyword signals a conditional in COOK. These operate over two lines of code, with the first being the condition and the second being the considered action. You will need to use the `the` reference key here. COOK has built-in functionality to compare the sizes of integers, as well as the equality of strings:
```
If the chicken is more than the rice,
in the bowl, mix the chicken and the rice.

If the string1 is the same brand as the string2,
in the bowl, mix the chicken and the rice.
```
For integers, you can use `is more than`, `is less than`, `is equal to`, and more (check the section on COOK's <a href="https://github.com/ishaan-awasthi/COOK?tab=readme-ov-file#very-limited-standard-library">Standard Library</a>).




<p> </p>
<h1>Loops</h1>

COOK has functionality for reverse while loops, signaled by the `until` key. These also operate over two lines of code, with the first being the loop operator and the second being the considered action. You will again use the `the` reference key here. Loops have the same built-in checks for integers as conditionals:

```
Until the bowl is equal to the rice,
in the bowl, mix the rice and the 1.
```
Once again, check the section on COOK's <a href="https://github.com/ishaan-awasthi/COOK?tab=readme-ov-file#very-limited-standard-library">Standard Library</a> for additional loop argument options!




<p> </p>
<h1>(Very Limited) Standard Library</h1>

Finally, COOK has a built-in Standard Library with a limited implementation of useful functions, arguments, and capabilities.

<h2>"Serve" Key: Output</h2>

Likely to be your most used of the built-in functions, `serve` is the key serving as COOK's equivalent to Python's `print` or Java's `System.out` (which COOK by nature utilizes). You can use it to display variables and standalone strings to the standard output stream (your IDE's process terminal). Usage is as follows:
```
Serve the "potatoes".
Serve the potatoes.
```
Note the distinction between the two lines: the former simply outputs the string **"_potatoes_"** to the terminal, while the latter accesses some previously declared variable `potatoes`, either an integer or string, and returns the associated value to print. Both usages still require a reference key!

<h2>"Find" Key: Runtime User Input</h2>

While the program is compiling, you can prompt for user input through the terminal using the `find` key. There are separate implementations for integers and for strings:
```
Find how much of the intvariable you have.
Find what brand of the stringvariable you have.
```
In both cases, the compiler will pause execution until the user inputs a valid input.

<h2>"Is Gone" Argument: Conditionals/Loops</h2>

In addition to the variable-variable comparisons utilized by COOK's conditionals and loops, an additional argument `is gone` is defined. This built-in condition checks whether the referenced integer variable is equal to zero, allowing for a more elegant syntax in specific cases. See the included `sample.txt` COOK program for an example of this operator in action.

<h4>Alternative Filetypes</h4>

While the standard input for COOK is `.txt` files, certain other filetypes may also work. Alternative filetypes range from `.md`, to `.csv`, all the way to even `.py`; if it can be accessed and read as plain text, it should theoretically be compatible with COOK. However, depending on your JDK version, `.java` files themselves may fail as the `util.Scanner` module processes them differently and will expect some kind of class declaration in the header.




<p> </p>
<h1>Closing Thoughts</h1>

I've always believed that cooking and coding, though seemingly distinct, share a remarkable overlap in terms of originality, precision, and the beauty of creation. By creating this esoteric fusion of those two worlds, I hope to offer a unique playground for programmers of all levels. Whether you're just learning the basics or have been coding for years, I invite you to to explore this world where scripts and recipes are synonymous, and where the syntax you choose to use is just as flexible as your inner chef's palate.

As you delve into COOK, remember that its purpose isn't just functionality; it's about the journey of discovery, the joy of experimentation, and the satisfaction of crafting something uniquely your own. So, grab that favorite spatula, fire up your IDE, and let's embark on a culinary adventure through code!


<p><b>Bon appétit, and happy coding!</b></p>
<p><b>— Ishaan Awasthi</b></p>


![image (1) (1)](https://github.com/ishaan-awasthi/COOK/assets/136520517/440b5578-f4b0-42f7-a36c-4fe374e4edc6)
