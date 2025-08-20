import sqlite3
import requests
import feedparser

# ========== CONFIG ==========
DB_FILE = "papers.db"
ARXIV_QUERY = "cat:cs.RO OR cat:physics.flu-dyn"   # Robotics + CFD
MAX_RESULTS = 10   # Number of papers to fetch
# =============================


def fetch_from_arxiv(query, max_results=5):
    """Fetch papers from arXiv API and return list of dicts"""
    url = f"http://export.arxiv.org/api/query?search_query={query}&max_results={max_results}"
    feed = feedparser.parse(requests.get(url).text)
    papers = []

    for entry in feed.entries:
        paper = {
            "id": entry.id.split("/abs/")[-1],
            "title": entry.title.replace("\n", " ").strip(),
            "authors": ", ".join(author.name for author in entry.authors),
            "year": entry.published.split("-")[0],
            "category": entry.tags[0]['term'] if entry.tags else "unknown",
            "abstract": entry.summary.replace("\n", " ").strip(),
            "pdf_url": entry.link.replace("abs", "pdf")
        }
        papers.append(paper)
    return papers


def init_db(db_file):
    """Create a SQLite database with papers table"""
    conn = sqlite3.connect(db_file)
    cur = conn.cursor()
    cur.execute("""
        CREATE TABLE IF NOT EXISTS papers (
            id TEXT PRIMARY KEY,
            title TEXT,
            authors TEXT,
            year INT,
            category TEXT,
            abstract TEXT,
            pdf_url TEXT
        )
    """)
    conn.commit()
    return conn


def insert_papers(conn, papers):
    """Insert papers into SQLite database"""
    cur = conn.cursor()
    for p in papers:
        try:
            cur.execute("""
                INSERT INTO papers (id, title, authors, year, category, abstract, pdf_url)
                VALUES (?, ?, ?, ?, ?, ?, ?)
            """, (p["id"], p["title"], p["authors"], p["year"], p["category"], p["abstract"], p["pdf_url"]))
        except sqlite3.IntegrityError:
            # Skip if already in DB
            pass
    conn.commit()


if __name__ == "__main__":
    conn = init_db(DB_FILE)
    papers = fetch_from_arxiv(ARXIV_QUERY, MAX_RESULTS)
    insert_papers(conn, papers)

    # Quick check: print first few titles
    cur = conn.cursor()
    cur.execute("SELECT id, title FROM papers LIMIT 5")
    for row in cur.fetchall():
        print(row)