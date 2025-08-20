import sqlite3

def querysearch(query, db_file='papers.db'):
    conn = sqlite3.connect(db_file)
    cur = conn.cursor()

    cur.execute(
        """SELECT id, title, authors, year, month, category, abstract, pdf_url 
        FROM papers 
        WHERE title LIKE ? OR abstract LIKE ? OR category LIKE ?""", (f"%{query}%", f"%{query}%", f"%{query}%"))
    
    rows = cur.fetchall()
    conn.close()

    papers = []
    for row in rows:
        papers.append({
            "id": row[0],
            "title": row[1],
            "authors": row[2],
            "year": row[3],
            "month": row[4],
            "category": row[5],
            "abstract": row[6],
            "pdf_url": row[7],
        })
    return papers