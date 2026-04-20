import markdown 

with open("vector.md") as f:
    text = f.read()

html = markdown.markdown(text, extensions=['fenced_code', 'tables', 'toc'])

with open("stl.html", 'w') as f:
    f.write(html)

