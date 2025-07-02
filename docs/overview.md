# DjVu Shape Extractor: `revealshapes`

`revealshapes` is a command-line tool for analyzing the shape dictionaries embedded in DjVu files, particularly focusing on JB2 image layers that encode text and line art.

---

## 🔍 Purpose

The tool extracts and reports detailed information about **blits** and their corresponding **shapes** on each page of a DjVu document.

> 📙 **Blits** are placed instances of shapes.  
> 📦 **Shapes** are reusable glyph-like bitmap patterns, optionally inherited from a shared dictionary.

---

## 📆 What It Outputs

For each shape usage (blit), the program prints:

```text
s|d,<page>,<blit#>,<shape#>,<columns>,<rows>,<rowsize>,<bottom>,<left>
```

Where:
- `s` or `d`: shape is **shared (inherited)** or **document-local**
- `<columns>`, `<rows>`, `<rowsize>`: bitmap geometry
- `<bottom>`, `<left>`: placement on the page

Alternatively, with the `-p` option, it emits Poliqarp-compatible `djvuopts` hyperlinks.

---

## ⚙️ Command-Line Options

| Option | Description |
|--------|-------------|
| `-f <n>` | Start from page number `n` |
| `-t <n>` | Stop at page number `n` |
| `-T`     | Verbose/debug mode |
| `-p`     | Output links for Poliqarp indexing |
| `-l`     | Output only links (currently unused) |

---

## 🚫 Features Removed from Original Version

- Database exporting code (originally part of `exportshapes.cpp`)
- Shape comparison pipeline (`jb2cmp` directory and tools)
- Any dependencies on Qt GUI elements

---

## 💡 Future Work

This tool is meant to be used as a shape extraction backend. It can be paired with:
- Visualization or labeling tools
- Post-processing scripts for pattern analysis or OCR prefiltering

---

## 🧑‍💻 Author Attribution

This tool is a fork of Piotr Sikora's original shape tools, further simplified by GitHub user [`rmast`](https://github.com/rmast).
