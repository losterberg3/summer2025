import sqlite3
import requests
import feedparser
import re


DB_FILE = "papers.db"
ARXIV_QUERY = "cat:cs.RO OR cat:physics.flu-dyn OR cat:cs.CV" 
MAX_RESULTS = 300


def fetch_from_arxiv(query, max_results):
    """Fetch papers from arXiv API and return list of dicts"""
    url = f"http://export.arxiv.org/api/query?search_query={query}&max_results={max_results}"
    feed = feedparser.parse(requests.get(url).text)
    papers = []

    for entry in feed.entries:
        paper = {
            "id": entry.id.split("/abs/")[-1],
            "title": re.sub(r'\s+', ' ', entry.title).strip(),
            "authors": ", ".join(author.name for author in entry.authors),
            "year": int(entry.published.split("-")[0]),
            "month": int(entry.published.split("-")[1]),
            "category": ", ".join(tag['term'] for tag in entry.tags) if entry.tags else "unknown",
            "abstract": re.sub(r'\s+', ' ', entry.summary).strip(),
            "pdf_url": entry.links[0]['href'].replace("abs", "pdf")
        }
        papers.append(paper)
    return papers

def insert_papers(conn, papers):
    """Insert papers into SQLite database if they aren't in there already"""
    cur = conn.cursor()
    for p in papers:
        try:
            cur.execute("""
                INSERT OR IGNORE INTO papers (id, title, authors, year, month, category, abstract, pdf_url)
                VALUES (?, ?, ?, ?, ?, ?, ?, ?)
            """, (p["id"], p["title"], p["authors"], p["year"], p["month"], p["category"], p["abstract"], p["pdf_url"]))
        except sqlite3.IntegrityError:
            pass
    conn.commit()

if __name__ == "__main__":
    conn = sqlite3.connect(DB_FILE)
    papers = fetch_from_arxiv(ARXIV_QUERY, MAX_RESULTS)
    insert_papers(conn, papers)

    cur = conn.cursor()
    i = 0
    cur.execute("SELECT id FROM papers LIMIT 400")
    for row in cur.fetchall():
        i=i+1
        if i%10 == 0:
            print(i)
   
    conn.close()