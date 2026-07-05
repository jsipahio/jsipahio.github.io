# Example Markdown
Markdown is a markup language that is simpler to use than HTML for creating formatted text documents. 
## Basic Markdown Elements
Here, we'll discuss the basic Markdown elements.
### Header Elements
Header elements start with a pound symbol #, and represent the h1-h5 HTML elements. A single pound symbol is h1, two are h2, etc. There needs to be a space between the pound symbol(s) and any text in the header for it to be parsed as a header.
### List Elements
A list is created by writing a dash/hyphen - at the start of a line. List items can be nested, but we won't consider them for the converter. Here is an example list.
- First Item
- Second Item
- Third Item
### Paragraph Elements
Text that is on its own line is treated as a paragraph. One thing we won't consider in the parser is that paragraphs are technically ended by two spaces and a new line, instead of a single newline. In our parser, however, we'll consider a new line to be the end of a paragraph.
### Other Elements That We Won't Handle
We aren't going to handle any nested formatting elements, like `code`, *italic*, and **bold** text. We also won't handle fenced code blocks, numbered lists, and tables. 
