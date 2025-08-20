import re
import sqlite3
from searchsqlite import querysearch

def main():
    print("Welcome to your Research Copilot!")
    while True:
        query = input("\nEnter a topic or keyword (or 'exit' to quit): ").strip()
        if query.lower() == "exit":
            break

        results = querysearch(query)
        if not results:
            print("No papers found for this query.")
            continue

        print(f"\nTop {len(results)} papers for '{query}':\n")
        for i, paper in enumerate(results, 1):
            print(f"{i}. {paper['title']} ({paper['year']})")
            print(f"   Authors: {paper['authors']}")
            print(f"   Category: {paper['category']}")
            print(f"   Abstract: {paper['abstract'][:200]}...")
            print(f"   PDF: {paper['pdf_url']}\n")

if __name__ == "__main__":
    main()