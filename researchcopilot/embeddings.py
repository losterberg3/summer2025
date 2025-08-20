import sqlite3
import numpy as np
from sentence_transformers import SentenceTransformer

DB_FILE = "papers.db"
MODEL = SentenceTransformer("all-MiniLM-L6-v2")

def embedvectors(db_file, model):
    conn = sqlite3.connect(db_file)
    rows = conn.cursor().execute("SELECT id, title, abstract FROM papers").fetchall()

    for pid, title, abstract in rows:
        text = f"{title}. {abstract}"
        embedding = model.encode(text, convert_to_numpy=True, normalize_embeddings=True)

        embedding_bytes = embedding.astype(np.float32).tobytes()

        conn.cursor().execute("UPDATE papers SET embedding = ? WHERE id = ?", (embedding_bytes, pid))

    conn.commit()
    conn.close()

def searchpapers(query, model, db_file, top_k=5):
    conn = sqlite3.connect(db_file)
    cursor = conn.cursor()

    rows = cursor.execute("SELECT id, title, abstract, embedding FROM papers").fetchall()
    conn.close()

    paper_ids, titles, abstracts, embeddings = [], [], [], []

    for pid, title, abstract, emb_bytes in rows:
        paper_ids.append(pid)
        titles.append(title)
        abstracts.append(abstract)
        embeddings.append(np.frombuffer(emb_bytes, dtype=np.float32))

    embeddings = np.vstack(embeddings)

    query_emb = model.encode([query], convert_to_numpy=True, normalize_embeddings=True)

    scores = np.dot(query_emb, embeddings)[0]
    top_idx = np.argsort(scores)[::-1][:top_k]

    results = [(titles[i], paper_ids[i], scores[i]) for i in top_idx]
    conn.close()
    return results

if __name__ == "__main__":
    conn = sqlite3.connect(DB_FILE)
    conn.cursor().execute("""ALTER TABLE papers ADD COLUMN embedding BLOB""")
    conn.commit()
    conn.close()

    embedvectors(DB_FILE, MODEL)
    QUERY = []
    searchpapers(QUERY, MODEL, DB_FILE)


